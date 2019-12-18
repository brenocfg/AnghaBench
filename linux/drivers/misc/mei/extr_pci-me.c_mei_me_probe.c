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
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct mei_me_hw {scalar_t__ d0i3_supported; int /*<<< orphan*/  mem_addr; } ;
struct mei_device {int dummy; } ;
struct mei_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DPM_FLAG_NEVER_SKIP ; 
 int ENODEV ; 
 int ENOMEM ; 
 unsigned int IRQF_ONESHOT ; 
 unsigned int IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MEI_ME_RPM_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mei_device*) ; 
 int /*<<< orphan*/  mei_cancel_work (struct mei_device*) ; 
 int /*<<< orphan*/  mei_disable_interrupts (struct mei_device*) ; 
 struct mei_device* mei_me_dev_init (struct pci_dev*,struct mei_cfg const*) ; 
 struct mei_cfg* mei_me_get_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_irq_quick_handler ; 
 int /*<<< orphan*/  mei_me_irq_thread_handler ; 
 int /*<<< orphan*/  mei_me_quirk_probe (struct pci_dev*,struct mei_cfg const*) ; 
 int /*<<< orphan*/  mei_me_set_pm_domain (struct mei_device*) ; 
 scalar_t__ mei_pg_is_enabled (struct mei_device*) ; 
 int mei_register (struct mei_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ mei_start (struct mei_device*) ; 
 int /*<<< orphan*/  mei_stop (struct mei_device*) ; 
 scalar_t__ pci_dev_msi_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct mei_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct mei_device*) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 

__attribute__((used)) static int mei_me_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	const struct mei_cfg *cfg;
	struct mei_device *dev;
	struct mei_me_hw *hw;
	unsigned int irqflags;
	int err;

	cfg = mei_me_get_cfg(ent->driver_data);
	if (!cfg)
		return -ENODEV;

	if (!mei_me_quirk_probe(pdev, cfg))
		return -ENODEV;

	/* enable pci dev */
	err = pcim_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "failed to enable pci device.\n");
		goto end;
	}
	/* set PCI host mastering  */
	pci_set_master(pdev);
	/* pci request regions and mapping IO device memory for mei driver */
	err = pcim_iomap_regions(pdev, BIT(0), KBUILD_MODNAME);
	if (err) {
		dev_err(&pdev->dev, "failed to get pci regions.\n");
		goto end;
	}

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(64)) ||
	    dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64))) {

		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		if (err)
			err = dma_set_coherent_mask(&pdev->dev,
						    DMA_BIT_MASK(32));
	}
	if (err) {
		dev_err(&pdev->dev, "No usable DMA configuration, aborting\n");
		goto end;
	}

	/* allocates and initializes the mei dev structure */
	dev = mei_me_dev_init(pdev, cfg);
	if (!dev) {
		err = -ENOMEM;
		goto end;
	}
	hw = to_me_hw(dev);
	hw->mem_addr = pcim_iomap_table(pdev)[0];

	pci_enable_msi(pdev);

	 /* request and enable interrupt */
	irqflags = pci_dev_msi_enabled(pdev) ? IRQF_ONESHOT : IRQF_SHARED;

	err = request_threaded_irq(pdev->irq,
			mei_me_irq_quick_handler,
			mei_me_irq_thread_handler,
			irqflags, KBUILD_MODNAME, dev);
	if (err) {
		dev_err(&pdev->dev, "request_threaded_irq failure. irq = %d\n",
		       pdev->irq);
		goto end;
	}

	if (mei_start(dev)) {
		dev_err(&pdev->dev, "init hw failure.\n");
		err = -ENODEV;
		goto release_irq;
	}

	pm_runtime_set_autosuspend_delay(&pdev->dev, MEI_ME_RPM_TIMEOUT);
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
	 * ME maps runtime suspend/resume to D0i states,
	 * hence we need to go around native PCI runtime service which
	 * eventually brings the device into D3cold/hot state,
	 * but the mei device cannot wake up from D3 unlike from D0i3.
	 * To get around the PCI device native runtime pm,
	 * ME uses runtime pm domain handlers which take precedence
	 * over the driver's pm handlers.
	 */
	mei_me_set_pm_domain(dev);

	if (mei_pg_is_enabled(dev)) {
		pm_runtime_put_noidle(&pdev->dev);
		if (hw->d0i3_supported)
			pm_runtime_allow(&pdev->dev);
	}

	dev_dbg(&pdev->dev, "initialization successful.\n");

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