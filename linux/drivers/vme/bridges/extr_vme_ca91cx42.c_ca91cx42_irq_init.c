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
struct vme_bridge {int /*<<< orphan*/  parent; struct ca91cx42_driver* driver_priv; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct ca91cx42_driver {scalar_t__ base; } ;

/* Variables and functions */
 int CA91CX42_LINT_DMA ; 
 int CA91CX42_LINT_LERR ; 
 int CA91CX42_LINT_MBOX0 ; 
 int CA91CX42_LINT_MBOX1 ; 
 int CA91CX42_LINT_MBOX2 ; 
 int CA91CX42_LINT_MBOX3 ; 
 int CA91CX42_LINT_SW_IACK ; 
 int CA91CX42_LINT_VERR ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ LINT_EN ; 
 scalar_t__ LINT_MAP0 ; 
 scalar_t__ LINT_MAP1 ; 
 scalar_t__ LINT_MAP2 ; 
 scalar_t__ LINT_STAT ; 
 scalar_t__ VINT_EN ; 
 int /*<<< orphan*/  ca91cx42_irqhandler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vme_bridge*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca91cx42_irq_init(struct vme_bridge *ca91cx42_bridge)
{
	int result, tmp;
	struct pci_dev *pdev;
	struct ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	/* Need pdev */
	pdev = to_pci_dev(ca91cx42_bridge->parent);

	/* Disable interrupts from PCI to VME */
	iowrite32(0, bridge->base + VINT_EN);

	/* Disable PCI interrupts */
	iowrite32(0, bridge->base + LINT_EN);
	/* Clear Any Pending PCI Interrupts */
	iowrite32(0x00FFFFFF, bridge->base + LINT_STAT);

	result = request_irq(pdev->irq, ca91cx42_irqhandler, IRQF_SHARED,
			driver_name, ca91cx42_bridge);
	if (result) {
		dev_err(&pdev->dev, "Can't get assigned pci irq vector %02X\n",
		       pdev->irq);
		return result;
	}

	/* Ensure all interrupts are mapped to PCI Interrupt 0 */
	iowrite32(0, bridge->base + LINT_MAP0);
	iowrite32(0, bridge->base + LINT_MAP1);
	iowrite32(0, bridge->base + LINT_MAP2);

	/* Enable DMA, mailbox & LM Interrupts */
	tmp = CA91CX42_LINT_MBOX3 | CA91CX42_LINT_MBOX2 | CA91CX42_LINT_MBOX1 |
		CA91CX42_LINT_MBOX0 | CA91CX42_LINT_SW_IACK |
		CA91CX42_LINT_VERR | CA91CX42_LINT_LERR | CA91CX42_LINT_DMA;

	iowrite32(tmp, bridge->base + LINT_EN);

	return 0;
}