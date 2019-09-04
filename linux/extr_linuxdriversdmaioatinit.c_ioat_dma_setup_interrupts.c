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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; struct device dev; } ;
struct msix_entry {int entry; int /*<<< orphan*/  vector; } ;
struct TYPE_2__ {int chancnt; } ;
struct ioatdma_device {int /*<<< orphan*/  irq_mode; scalar_t__ reg_base; struct msix_entry* msix_entries; TYPE_1__ dma_dev; struct pci_dev* pdev; } ;
struct ioatdma_chan {int /*<<< orphan*/  irq_mode; scalar_t__ reg_base; struct msix_entry* msix_entries; TYPE_1__ dma_dev; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IOAT_INTRCTRL_MASTER_INT_EN ; 
 int /*<<< orphan*/  IOAT_INTRCTRL_MSIX_VECTOR_CONTROL ; 
 scalar_t__ IOAT_INTRCTRL_OFFSET ; 
 int /*<<< orphan*/  IOAT_INTX ; 
 int /*<<< orphan*/  IOAT_MSI ; 
 int /*<<< orphan*/  IOAT_MSIX ; 
 int /*<<< orphan*/  IOAT_NOIRQ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_free_irq (struct device*,int /*<<< orphan*/ ,struct ioatdma_device*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ioatdma_device*) ; 
 struct ioatdma_device* ioat_chan_by_index (struct ioatdma_device*,int) ; 
 int /*<<< orphan*/  ioat_dma_do_interrupt ; 
 int /*<<< orphan*/  ioat_dma_do_interrupt_msix ; 
 int /*<<< orphan*/  ioat_interrupt_style ; 
 int /*<<< orphan*/  ioat_intr_quirk (struct ioatdma_device*) ; 
 scalar_t__ is_bwd_ioat (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int pci_enable_msi (struct pci_dev*) ; 
 int pci_enable_msix_exact (struct pci_dev*,struct msix_entry*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

int ioat_dma_setup_interrupts(struct ioatdma_device *ioat_dma)
{
	struct ioatdma_chan *ioat_chan;
	struct pci_dev *pdev = ioat_dma->pdev;
	struct device *dev = &pdev->dev;
	struct msix_entry *msix;
	int i, j, msixcnt;
	int err = -EINVAL;
	u8 intrctrl = 0;

	if (!strcmp(ioat_interrupt_style, "msix"))
		goto msix;
	if (!strcmp(ioat_interrupt_style, "msi"))
		goto msi;
	if (!strcmp(ioat_interrupt_style, "intx"))
		goto intx;
	dev_err(dev, "invalid ioat_interrupt_style %s\n", ioat_interrupt_style);
	goto err_no_irq;

msix:
	/* The number of MSI-X vectors should equal the number of channels */
	msixcnt = ioat_dma->dma_dev.chancnt;
	for (i = 0; i < msixcnt; i++)
		ioat_dma->msix_entries[i].entry = i;

	err = pci_enable_msix_exact(pdev, ioat_dma->msix_entries, msixcnt);
	if (err)
		goto msi;

	for (i = 0; i < msixcnt; i++) {
		msix = &ioat_dma->msix_entries[i];
		ioat_chan = ioat_chan_by_index(ioat_dma, i);
		err = devm_request_irq(dev, msix->vector,
				       ioat_dma_do_interrupt_msix, 0,
				       "ioat-msix", ioat_chan);
		if (err) {
			for (j = 0; j < i; j++) {
				msix = &ioat_dma->msix_entries[j];
				ioat_chan = ioat_chan_by_index(ioat_dma, j);
				devm_free_irq(dev, msix->vector, ioat_chan);
			}
			goto msi;
		}
	}
	intrctrl |= IOAT_INTRCTRL_MSIX_VECTOR_CONTROL;
	ioat_dma->irq_mode = IOAT_MSIX;
	goto done;

msi:
	err = pci_enable_msi(pdev);
	if (err)
		goto intx;

	err = devm_request_irq(dev, pdev->irq, ioat_dma_do_interrupt, 0,
			       "ioat-msi", ioat_dma);
	if (err) {
		pci_disable_msi(pdev);
		goto intx;
	}
	ioat_dma->irq_mode = IOAT_MSI;
	goto done;

intx:
	err = devm_request_irq(dev, pdev->irq, ioat_dma_do_interrupt,
			       IRQF_SHARED, "ioat-intx", ioat_dma);
	if (err)
		goto err_no_irq;

	ioat_dma->irq_mode = IOAT_INTX;
done:
	if (is_bwd_ioat(pdev))
		ioat_intr_quirk(ioat_dma);
	intrctrl |= IOAT_INTRCTRL_MASTER_INT_EN;
	writeb(intrctrl, ioat_dma->reg_base + IOAT_INTRCTRL_OFFSET);
	return 0;

err_no_irq:
	/* Disable all interrupt generation */
	writeb(0, ioat_dma->reg_base + IOAT_INTRCTRL_OFFSET);
	ioat_dma->irq_mode = IOAT_NOIRQ;
	dev_err(dev, "no usable interrupts\n");
	return err;
}