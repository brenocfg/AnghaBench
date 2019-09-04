#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct nes_device {int napi_isr_ran; int int_stat; int int_req; size_t nic_ceq_index; scalar_t__ deepcq_count; int timer_int_req; int intf_int_req; scalar_t__ regs; struct nes_adapter* nesadapter; } ;
struct nes_adapter {int et_use_adaptive_rx_coalesce; scalar_t__ et_pkt_rate_low; int timer_int_req; scalar_t__ et_rx_coalesce_usecs_irq; int /*<<< orphan*/ * ceq; } ;

/* Variables and functions */
 scalar_t__ NES_INTF_INT_MASK ; 
 int NES_INTF_PERIODIC_TIMER ; 
 int NES_INT_INTF ; 
 int NES_INT_MAC0 ; 
 int NES_INT_MAC1 ; 
 int NES_INT_MAC2 ; 
 int NES_INT_MAC3 ; 
 scalar_t__ NES_INT_MASK ; 
 scalar_t__ NES_INT_STAT ; 
 int NES_INT_TIMER ; 
 scalar_t__ NES_TIMER_STAT ; 
 int /*<<< orphan*/  nes_nic_init_timer (struct nes_device*) ; 
 int /*<<< orphan*/  nes_process_ceq (struct nes_device*,int /*<<< orphan*/ *) ; 
 int nes_read32 (scalar_t__) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 

int nes_napi_isr(struct nes_device *nesdev)
{
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	u32 int_stat;

	if (nesdev->napi_isr_ran) {
		/* interrupt status has already been read in ISR */
		int_stat = nesdev->int_stat;
	} else {
		int_stat = nes_read32(nesdev->regs + NES_INT_STAT);
		nesdev->int_stat = int_stat;
		nesdev->napi_isr_ran = 1;
	}

	int_stat &= nesdev->int_req;
	/* iff NIC, process here, else wait for DPC */
	if ((int_stat) && ((int_stat & 0x0000ff00) == int_stat)) {
		nesdev->napi_isr_ran = 0;
		nes_write32(nesdev->regs + NES_INT_STAT,
			(int_stat &
			~(NES_INT_INTF | NES_INT_TIMER | NES_INT_MAC0 | NES_INT_MAC1 | NES_INT_MAC2 | NES_INT_MAC3)));

		/* Process the CEQs */
		nes_process_ceq(nesdev, &nesdev->nesadapter->ceq[nesdev->nic_ceq_index]);

		if (unlikely((((nesadapter->et_rx_coalesce_usecs_irq) &&
					(!nesadapter->et_use_adaptive_rx_coalesce)) ||
					((nesadapter->et_use_adaptive_rx_coalesce) &&
					 (nesdev->deepcq_count > nesadapter->et_pkt_rate_low))))) {
			if ((nesdev->int_req & NES_INT_TIMER) == 0) {
				/* Enable Periodic timer interrupts */
				nesdev->int_req |= NES_INT_TIMER;
				/* ack any pending periodic timer interrupts so we don't get an immediate interrupt */
				/* TODO: need to also ack other unused periodic timer values, get from nesadapter */
				nes_write32(nesdev->regs+NES_TIMER_STAT,
						nesdev->timer_int_req  | ~(nesdev->nesadapter->timer_int_req));
				nes_write32(nesdev->regs+NES_INTF_INT_MASK,
						~(nesdev->intf_int_req | NES_INTF_PERIODIC_TIMER));
			}

			if (unlikely(nesadapter->et_use_adaptive_rx_coalesce))
			{
				nes_nic_init_timer(nesdev);
			}
			/* Enable interrupts, except CEQs */
			nes_write32(nesdev->regs+NES_INT_MASK, 0x0000ffff | (~nesdev->int_req));
		} else {
			/* Enable interrupts, make sure timer is off */
			nesdev->int_req &= ~NES_INT_TIMER;
			nes_write32(nesdev->regs+NES_INTF_INT_MASK, ~(nesdev->intf_int_req));
			nes_write32(nesdev->regs+NES_INT_MASK, ~nesdev->int_req);
		}
		nesdev->deepcq_count = 0;
		return 1;
	} else {
		return 0;
	}
}