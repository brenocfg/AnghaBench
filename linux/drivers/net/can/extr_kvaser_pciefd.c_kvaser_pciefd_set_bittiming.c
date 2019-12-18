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
typedef  int u32 ;
struct can_bittiming {int phase_seg2; int prop_seg; int phase_seg1; int sjw; int brp; } ;
struct TYPE_2__ {struct can_bittiming bittiming; struct can_bittiming data_bittiming; } ;
struct kvaser_pciefd_can {int /*<<< orphan*/  lock; scalar_t__ reg_base; TYPE_1__ can; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ KVASER_PCIEFD_KCAN_BTRD_REG ; 
 scalar_t__ KVASER_PCIEFD_KCAN_BTRN_REG ; 
 int KVASER_PCIEFD_KCAN_BTRN_SJW_SHIFT ; 
 int KVASER_PCIEFD_KCAN_BTRN_TSEG1_SHIFT ; 
 int KVASER_PCIEFD_KCAN_BTRN_TSEG2_SHIFT ; 
 scalar_t__ KVASER_PCIEFD_KCAN_MODE_REG ; 
 int KVASER_PCIEFD_KCAN_MODE_RM ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int kvaser_pciefd_set_bittiming(struct kvaser_pciefd_can *can, bool data)
{
	u32 mode, test, btrn;
	unsigned long irq_flags;
	int ret;
	struct can_bittiming *bt;

	if (data)
		bt = &can->can.data_bittiming;
	else
		bt = &can->can.bittiming;

	btrn = ((bt->phase_seg2 - 1) & 0x1f) <<
	       KVASER_PCIEFD_KCAN_BTRN_TSEG2_SHIFT |
	       (((bt->prop_seg + bt->phase_seg1) - 1) & 0x1ff) <<
	       KVASER_PCIEFD_KCAN_BTRN_TSEG1_SHIFT |
	       ((bt->sjw - 1) & 0xf) << KVASER_PCIEFD_KCAN_BTRN_SJW_SHIFT |
	       ((bt->brp - 1) & 0x1fff);

	spin_lock_irqsave(&can->lock, irq_flags);
	mode = ioread32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);

	/* Put the circuit in reset mode */
	iowrite32(mode | KVASER_PCIEFD_KCAN_MODE_RM,
		  can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);

	/* Can only set bittiming if in reset mode */
	ret = readl_poll_timeout(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG,
				 test, test & KVASER_PCIEFD_KCAN_MODE_RM,
				 0, 10);

	if (ret) {
		spin_unlock_irqrestore(&can->lock, irq_flags);
		return -EBUSY;
	}

	if (data)
		iowrite32(btrn, can->reg_base + KVASER_PCIEFD_KCAN_BTRD_REG);
	else
		iowrite32(btrn, can->reg_base + KVASER_PCIEFD_KCAN_BTRN_REG);

	/* Restore previous reset mode status */
	iowrite32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);

	spin_unlock_irqrestore(&can->lock, irq_flags);
	return 0;
}