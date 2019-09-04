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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct mei_txe_hw {int /*<<< orphan*/  mem_addr; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRIDGE_BAR ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DPM_FLAG_NEVER_SKIP ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MEI_TXI_RPM_TIMEOUT ; 
 int /*<<< orphan*/  SEC_BAR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mei_device*) ; 
 int /*<<< orphan*/  mei_cancel_work (struct mei_device*) ; 
 int /*<<< orphan*/  mei_clear_interrupts (struct mei_device*) ; 
 int /*<<< orphan*/  mei_disable_interrupts (struct mei_device*) ; 
 int mei_register (struct mei_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ mei_start (struct mei_device*) ; 
 int /*<<< orphan*/  mei_stop (struct mei_device*) ; 
 struct mei_device* mei_txe_dev_init (struct pci_dev*) ; 
 int /*<<< orphan*/ * mei_txe_irq_quick_handler ; 
 int /*<<< orphan*/  mei_txe_irq_thread_handler ; 
 int /*<<< orphan*/  mei_txe_set_pm_domain (struct mei_device*) ; 
 scalar_t__ pci_dev_msi_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct mei_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mei_device*) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static int mei_txe_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct mei_device *dev;
	struct mei_txe_hw *hw;
	const int mask = BIT(SEC_BAR) | BIT(BRIDGE_BAR);
	int err;

	/* enable pci dev */
	err = pcim_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "failed to enable pci device.\n");
		goto end;
	}
	/* set PCI host mastering  */
	pci_set_master(pdev);
	/* pci request regions and mapping IO device memory for mei driver */
	err = pcim_iomap_regions(pdev, mask, KBUILD_MODNAME);
	if (err) {
		dev_err(&pdev->dev, "failed to get pci regions.\n");
		goto end;
	}

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(36));
	if (err) {
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (err) {
			dev_err(&pdev->dev, "No suitable DMA available.\n");
			goto end;
		}
	}

	/* allocates and initializes the mei dev structure */
	dev = mei_txe_dev_init(pdev);
	if (!dev) {
		err = -ENOMEM;
		goto end;
	}
	hw = to_txe_hw(dev);
	hw->mem_addr = pcim_iomap_table(pdev);

	pci_enable_msi(pdev);

	/* clear spurious interrupts */
	mei_clear_interrupts(dev);

	/* request and enable interrupt  */
	if (pci_dev_msi_enabled(pdev))
		err = request_threaded_irq(pdev->irq,
			NULL,
			mei_txe_irq_thread_handler,
			IRQF_ONESHOT, KBUILD_MODNAME, dev);
	else
		err = request_threaded_irq(pdev->irq,
			mei_txe_irq_quick_handler,
			mei_txe_irq_thread_handler,
			IRQF_SHARED, KBUILD_MODNAME, dev);
	if (err) {
		dev_err(&pdev->dev, "mei: request_threaded_irq failure. irq = %d\n",
			pdev->irq);
		goto end;
	}

	if (mei_start(dev)) {
		dev_err(&pdev->dev, "init hw failure.\n");
		err = -ENODEV;
		goto release_irq;
	}

	pm_runtime_set_autosuspend_delay(&pdev->dev, MEI_TXI_RPM_TIMEOUT);
	pm_runtime_use_autosuspend(&pdev->dev);

	err = mei_register(dev, &pdev->dev);
	if (err)
		goto stop;

	pci_set_drvdata(pdev, dev);

	/*
	 * MEI requires to resume from runtime suspend mode
	 * in order to perform link reset flow upon system suspend.
	 */
	dev_pm_set_driver_flags(&pdev->dev, DPM_FLAG_NEVER_SKIP);

	/*
	 * TXE maps runtime suspend/resume to own power gating states,
	 * hence we need to go around native PCI runtime service which
	 * eventually brings the device into D3cold/hot state.
	 * But the TXE device cannot wake up from D3 unlike from own
	 * power gating. To get around PCI device native runtime pm,
	 * TXE uses runtime pm domain handlers which take precedence.
	 */
	mei_txe_set_pm_domain(dev);

	pm_runtime_put_noidle(&pdev->dev);

	return 0;

stop:
	mei_stop(dev);
release_irq:
	mei_cancel_work(dev);
	mei_disable_interrupts(dev);
	free_irq(pdev->irq, dev);
end:
	dev_err(&pdev->dev, "initialization failed.\n");
	return err;
}