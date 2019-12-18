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
struct kvaser_pciefd {int nr_channels; scalar_t__ reg_base; int /*<<< orphan*/ * can; TYPE_1__* pci; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int KVASER_PCIEFD_IRQ_ALL_MSK ; 
 scalar_t__ KVASER_PCIEFD_IRQ_REG ; 
 int KVASER_PCIEFD_IRQ_SRB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_receive_irq (struct kvaser_pciefd*) ; 
 int /*<<< orphan*/  kvaser_pciefd_transmit_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t kvaser_pciefd_irq_handler(int irq, void *dev)
{
	struct kvaser_pciefd *pcie = (struct kvaser_pciefd *)dev;
	u32 board_irq;
	int i;

	board_irq = ioread32(pcie->reg_base + KVASER_PCIEFD_IRQ_REG);

	if (!(board_irq & KVASER_PCIEFD_IRQ_ALL_MSK))
		return IRQ_NONE;

	if (board_irq & KVASER_PCIEFD_IRQ_SRB)
		kvaser_pciefd_receive_irq(pcie);

	for (i = 0; i < pcie->nr_channels; i++) {
		if (!pcie->can[i]) {
			dev_err(&pcie->pci->dev,
				"IRQ mask points to unallocated controller\n");
			break;
		}

		/* Check that mask matches channel (i) IRQ mask */
		if (board_irq & (1 << i))
			kvaser_pciefd_transmit_irq(pcie->can[i]);
	}

	iowrite32(board_irq, pcie->reg_base + KVASER_PCIEFD_IRQ_REG);
	return IRQ_HANDLED;
}