#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int dbb_irqs; } ;
struct TYPE_6__ {TYPE_1__ req; int /*<<< orphan*/  ac_wake_work; } ;
struct TYPE_5__ {int /*<<< orphan*/  sysclk_work; } ;

/* Variables and functions */
#define  MB0H_WAKEUP_EXE 129 
#define  MB0H_WAKEUP_SLEEP 128 
 int /*<<< orphan*/  MBOX_BIT (int /*<<< orphan*/ ) ; 
 unsigned int NUM_PRCMU_WAKEUPS ; 
 scalar_t__ PRCM_ACK_MB0_READ_POINTER ; 
 scalar_t__ PRCM_ACK_MB0_WAKEUP_0_8500 ; 
 scalar_t__ PRCM_ACK_MB0_WAKEUP_1_8500 ; 
 int /*<<< orphan*/  PRCM_ARM_IT1_CLR ; 
 scalar_t__ PRCM_MBOX_HEADER_ACK_MB0 ; 
 int WAKEUP_BIT_AC_SLEEP_ACK ; 
 int WAKEUP_BIT_AC_WAKE_ACK ; 
 int WAKEUP_BIT_SYSCLK_OK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db8500_irq_domain ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_3__ mb0_transfer ; 
 TYPE_2__ mb3_transfer ; 
 int* prcmu_irq_bit ; 
 int /*<<< orphan*/  print_unknown_header_warning (int /*<<< orphan*/ ,int) ; 
 int readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool read_mailbox_0(void)
{
	bool r;
	u32 ev;
	unsigned int n;
	u8 header;

	header = readb(tcdm_base + PRCM_MBOX_HEADER_ACK_MB0);
	switch (header) {
	case MB0H_WAKEUP_EXE:
	case MB0H_WAKEUP_SLEEP:
		if (readb(tcdm_base + PRCM_ACK_MB0_READ_POINTER) & 1)
			ev = readl(tcdm_base + PRCM_ACK_MB0_WAKEUP_1_8500);
		else
			ev = readl(tcdm_base + PRCM_ACK_MB0_WAKEUP_0_8500);

		if (ev & (WAKEUP_BIT_AC_WAKE_ACK | WAKEUP_BIT_AC_SLEEP_ACK))
			complete(&mb0_transfer.ac_wake_work);
		if (ev & WAKEUP_BIT_SYSCLK_OK)
			complete(&mb3_transfer.sysclk_work);

		ev &= mb0_transfer.req.dbb_irqs;

		for (n = 0; n < NUM_PRCMU_WAKEUPS; n++) {
			if (ev & prcmu_irq_bit[n])
				generic_handle_irq(irq_find_mapping(db8500_irq_domain, n));
		}
		r = true;
		break;
	default:
		print_unknown_header_warning(0, header);
		r = false;
		break;
	}
	writel(MBOX_BIT(0), PRCM_ARM_IT1_CLR);
	return r;
}