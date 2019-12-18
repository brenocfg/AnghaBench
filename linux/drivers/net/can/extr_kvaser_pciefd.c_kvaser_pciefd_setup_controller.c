#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int ctrlmode; } ;
struct kvaser_pciefd_can {int /*<<< orphan*/  lock; scalar_t__ reg_base; TYPE_1__ can; } ;

/* Variables and functions */
 int CAN_CTRLMODE_FD ; 
 int CAN_CTRLMODE_FD_NON_ISO ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_MODE_APT ; 
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_MODE_CCM ; 
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_MODE_EEN ; 
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_MODE_EPEN ; 
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_MODE_LOM ; 
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_MODE_NIFDEN ; 
 scalar_t__ KVASER_PCIEFD_KCAN_MODE_REG ; 
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_MODE_RM ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kvaser_pciefd_setup_controller(struct kvaser_pciefd_can *can)
{
	u32 mode;
	unsigned long irq;

	spin_lock_irqsave(&can->lock, irq);

	mode = ioread32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	if (can->can.ctrlmode & CAN_CTRLMODE_FD) {
		mode &= ~KVASER_PCIEFD_KCAN_MODE_CCM;
		if (can->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO)
			mode |= KVASER_PCIEFD_KCAN_MODE_NIFDEN;
		else
			mode &= ~KVASER_PCIEFD_KCAN_MODE_NIFDEN;
	} else {
		mode |= KVASER_PCIEFD_KCAN_MODE_CCM;
		mode &= ~KVASER_PCIEFD_KCAN_MODE_NIFDEN;
	}

	if (can->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		mode |= KVASER_PCIEFD_KCAN_MODE_LOM;

	mode |= KVASER_PCIEFD_KCAN_MODE_EEN;
	mode |= KVASER_PCIEFD_KCAN_MODE_EPEN;
	/* Use ACK packet type */
	mode &= ~KVASER_PCIEFD_KCAN_MODE_APT;
	mode &= ~KVASER_PCIEFD_KCAN_MODE_RM;
	iowrite32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);

	spin_unlock_irqrestore(&can->lock, irq);
}