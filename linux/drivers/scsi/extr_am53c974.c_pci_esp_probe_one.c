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
struct scsi_host_template {int dummy; } ;
struct pci_esp_priv {struct esp* esp; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct esp {int scsi_id; int scsi_id_mask; int cfreq; scalar_t__ regs; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  command_block; scalar_t__ dma_regs; int /*<<< orphan*/  config2; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; struct Scsi_Host* host; } ;
struct Scsi_Host {int this_id; int max_id; int /*<<< orphan*/  io_port; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  n_io_port; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_MODULE_NAME ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ESP_CONFIG2_FENAB ; 
 int /*<<< orphan*/  ESP_FLAG_USE_FIFO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ am53c974_fenab ; 
 int /*<<< orphan*/  dc390_check_eeprom (struct esp*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct esp*) ; 
 int /*<<< orphan*/  kfree (struct pci_esp_priv*) ; 
 struct pci_esp_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_esp_ops ; 
 scalar_t__ pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct pci_esp_priv*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct esp*) ; 
 int /*<<< orphan*/  scsi_esp_intr ; 
 int scsi_esp_register (struct esp*) ; 
 struct scsi_host_template scsi_esp_template ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct esp* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int pci_esp_probe_one(struct pci_dev *pdev,
			      const struct pci_device_id *id)
{
	struct scsi_host_template *hostt = &scsi_esp_template;
	int err = -ENODEV;
	struct Scsi_Host *shost;
	struct esp *esp;
	struct pci_esp_priv *pep;

	if (pci_enable_device(pdev)) {
		dev_printk(KERN_INFO, &pdev->dev, "cannot enable device\n");
		return -ENODEV;
	}

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		dev_printk(KERN_INFO, &pdev->dev,
			   "failed to set 32bit DMA mask\n");
		goto fail_disable_device;
	}

	shost = scsi_host_alloc(hostt, sizeof(struct esp));
	if (!shost) {
		dev_printk(KERN_INFO, &pdev->dev,
			   "failed to allocate scsi host\n");
		err = -ENOMEM;
		goto fail_disable_device;
	}

	pep = kzalloc(sizeof(struct pci_esp_priv), GFP_KERNEL);
	if (!pep) {
		dev_printk(KERN_INFO, &pdev->dev,
			   "failed to allocate esp_priv\n");
		err = -ENOMEM;
		goto fail_host_alloc;
	}

	esp = shost_priv(shost);
	esp->host = shost;
	esp->dev = &pdev->dev;
	esp->ops = &pci_esp_ops;
	/*
	 * The am53c974 HBA has a design flaw of generating
	 * spurious DMA completion interrupts when using
	 * DMA for command submission.
	 */
	esp->flags |= ESP_FLAG_USE_FIFO;
	/*
	 * Enable CONFIG2_FENAB to allow for large DMA transfers
	 */
	if (am53c974_fenab)
		esp->config2 |= ESP_CONFIG2_FENAB;

	pep->esp = esp;

	if (pci_request_regions(pdev, DRV_MODULE_NAME)) {
		dev_printk(KERN_ERR, &pdev->dev,
			   "pci memory selection failed\n");
		goto fail_priv_alloc;
	}

	esp->regs = pci_iomap(pdev, 0, pci_resource_len(pdev, 0));
	if (!esp->regs) {
		dev_printk(KERN_ERR, &pdev->dev, "pci I/O map failed\n");
		err = -EINVAL;
		goto fail_release_regions;
	}
	esp->dma_regs = esp->regs;

	pci_set_master(pdev);

	esp->command_block = dma_alloc_coherent(&pdev->dev, 16,
			&esp->command_block_dma, GFP_KERNEL);
	if (!esp->command_block) {
		dev_printk(KERN_ERR, &pdev->dev,
			   "failed to allocate command block\n");
		err = -ENOMEM;
		goto fail_unmap_regs;
	}

	pci_set_drvdata(pdev, pep);

	err = request_irq(pdev->irq, scsi_esp_intr, IRQF_SHARED,
			  DRV_MODULE_NAME, esp);
	if (err < 0) {
		dev_printk(KERN_ERR, &pdev->dev, "failed to register IRQ\n");
		goto fail_unmap_command_block;
	}

	esp->scsi_id = 7;
	dc390_check_eeprom(esp);

	shost->this_id = esp->scsi_id;
	shost->max_id = 8;
	shost->irq = pdev->irq;
	shost->io_port = pci_resource_start(pdev, 0);
	shost->n_io_port = pci_resource_len(pdev, 0);
	shost->unique_id = shost->io_port;
	esp->scsi_id_mask = (1 << esp->scsi_id);
	/* Assume 40MHz clock */
	esp->cfreq = 40000000;

	err = scsi_esp_register(esp);
	if (err)
		goto fail_free_irq;

	return 0;

fail_free_irq:
	free_irq(pdev->irq, esp);
fail_unmap_command_block:
	pci_set_drvdata(pdev, NULL);
	dma_free_coherent(&pdev->dev, 16, esp->command_block,
			  esp->command_block_dma);
fail_unmap_regs:
	pci_iounmap(pdev, esp->regs);
fail_release_regions:
	pci_release_regions(pdev);
fail_priv_alloc:
	kfree(pep);
fail_host_alloc:
	scsi_host_put(shost);
fail_disable_device:
	pci_disable_device(pdev);

	return err;
}