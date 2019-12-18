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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct kvaser_pciefd_can {scalar_t__ reg_base; TYPE_1__ can; } ;

/* Variables and functions */
 int KVASER_PCIEFD_KCAN_CTRL_EFLUSH ; 
 scalar_t__ KVASER_PCIEFD_KCAN_CTRL_REG ; 
 int KVASER_PCIEFD_KCAN_IRQ_BPP ; 
 int KVASER_PCIEFD_KCAN_IRQ_FDIC ; 
 scalar_t__ KVASER_PCIEFD_KCAN_IRQ_REG ; 
 int KVASER_PCIEFD_KCAN_IRQ_ROF ; 
 int KVASER_PCIEFD_KCAN_IRQ_TFD ; 
 int KVASER_PCIEFD_KCAN_IRQ_TOF ; 
 scalar_t__ KVASER_PCIEFD_KCAN_TX_NPACKETS_REG ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int kvaser_pciefd_transmit_irq(struct kvaser_pciefd_can *can)
{
	u32 irq = ioread32(can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);

	if (irq & KVASER_PCIEFD_KCAN_IRQ_TOF)
		netdev_err(can->can.dev, "Tx FIFO overflow\n");

	if (irq & KVASER_PCIEFD_KCAN_IRQ_TFD) {
		u8 count = ioread32(can->reg_base +
				    KVASER_PCIEFD_KCAN_TX_NPACKETS_REG) & 0xff;

		if (count == 0)
			iowrite32(KVASER_PCIEFD_KCAN_CTRL_EFLUSH,
				  can->reg_base + KVASER_PCIEFD_KCAN_CTRL_REG);
	}

	if (irq & KVASER_PCIEFD_KCAN_IRQ_BPP)
		netdev_err(can->can.dev,
			   "Fail to change bittiming, when not in reset mode\n");

	if (irq & KVASER_PCIEFD_KCAN_IRQ_FDIC)
		netdev_err(can->can.dev, "CAN FD frame in CAN mode\n");

	if (irq & KVASER_PCIEFD_KCAN_IRQ_ROF)
		netdev_err(can->can.dev, "Rx FIFO overflow\n");

	iowrite32(irq, can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);
	return 0;
}