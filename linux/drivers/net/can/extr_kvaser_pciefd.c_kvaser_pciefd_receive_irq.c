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
struct kvaser_pciefd {scalar_t__ reg_base; TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int KVASER_PCIEFD_SRB_CMD_RDB0 ; 
 int KVASER_PCIEFD_SRB_CMD_RDB1 ; 
 scalar_t__ KVASER_PCIEFD_SRB_CMD_REG ; 
 int KVASER_PCIEFD_SRB_IRQ_DOF0 ; 
 int KVASER_PCIEFD_SRB_IRQ_DOF1 ; 
 int KVASER_PCIEFD_SRB_IRQ_DPD0 ; 
 int KVASER_PCIEFD_SRB_IRQ_DPD1 ; 
 int KVASER_PCIEFD_SRB_IRQ_DUF0 ; 
 int KVASER_PCIEFD_SRB_IRQ_DUF1 ; 
 scalar_t__ KVASER_PCIEFD_SRB_IRQ_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_read_buffer (struct kvaser_pciefd*,int) ; 

__attribute__((used)) static int kvaser_pciefd_receive_irq(struct kvaser_pciefd *pcie)
{
	u32 irq;

	irq = ioread32(pcie->reg_base + KVASER_PCIEFD_SRB_IRQ_REG);
	if (irq & KVASER_PCIEFD_SRB_IRQ_DPD0) {
		kvaser_pciefd_read_buffer(pcie, 0);
		/* Reset DMA buffer 0 */
		iowrite32(KVASER_PCIEFD_SRB_CMD_RDB0,
			  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);
	}

	if (irq & KVASER_PCIEFD_SRB_IRQ_DPD1) {
		kvaser_pciefd_read_buffer(pcie, 1);
		/* Reset DMA buffer 1 */
		iowrite32(KVASER_PCIEFD_SRB_CMD_RDB1,
			  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);
	}

	if (irq & KVASER_PCIEFD_SRB_IRQ_DOF0 ||
	    irq & KVASER_PCIEFD_SRB_IRQ_DOF1 ||
	    irq & KVASER_PCIEFD_SRB_IRQ_DUF0 ||
	    irq & KVASER_PCIEFD_SRB_IRQ_DUF1)
		dev_err(&pcie->pci->dev, "DMA IRQ error 0x%08X\n", irq);

	iowrite32(irq, pcie->reg_base + KVASER_PCIEFD_SRB_IRQ_REG);
	return 0;
}