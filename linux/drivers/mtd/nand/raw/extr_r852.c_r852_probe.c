#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int strength; int /*<<< orphan*/  read_oob; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; int /*<<< orphan*/  hwctl; int /*<<< orphan*/  bytes; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  waitfunc; int /*<<< orphan*/  cmd_ctrl; } ;
struct r852_device {int /*<<< orphan*/  phys_bounce_buffer; int /*<<< orphan*/  bounce_buffer; int /*<<< orphan*/  mmio; struct r852_device* tmp_buffer; int /*<<< orphan*/  card_workqueue; int /*<<< orphan*/  card_detect_work; scalar_t__ card_detected; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  irq; int /*<<< orphan*/  dma_done; struct pci_dev* pci_dev; struct r852_device* chip; TYPE_2__ ecc; TYPE_1__ legacy; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct nand_chip {int /*<<< orphan*/  phys_bounce_buffer; int /*<<< orphan*/  bounce_buffer; int /*<<< orphan*/  mmio; struct nand_chip* tmp_buffer; int /*<<< orphan*/  card_workqueue; int /*<<< orphan*/  card_detect_work; scalar_t__ card_detected; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  irq; int /*<<< orphan*/  dma_done; struct pci_dev* pci_dev; struct nand_chip* chip; TYPE_2__ ecc; TYPE_1__ legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  NAND_ECC_HW_SYNDROME ; 
 int /*<<< orphan*/  R852_DMA_LEN ; 
 int /*<<< orphan*/  SM_OOB_SIZE ; 
 int SM_SECTOR_SIZE ; 
 int /*<<< orphan*/  create_freezable_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct r852_device*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct r852_device*,struct r852_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct r852_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_card_detect_work ; 
 int /*<<< orphan*/  r852_card_update_present (struct r852_device*) ; 
 int /*<<< orphan*/  r852_cmdctl ; 
 int /*<<< orphan*/  r852_disable_irqs (struct r852_device*) ; 
 int /*<<< orphan*/  r852_dma_test (struct r852_device*) ; 
 int /*<<< orphan*/  r852_ecc_calculate ; 
 int /*<<< orphan*/  r852_ecc_correct ; 
 int /*<<< orphan*/  r852_ecc_hwctl ; 
 int /*<<< orphan*/  r852_engine_disable (struct r852_device*) ; 
 int /*<<< orphan*/  r852_irq ; 
 int /*<<< orphan*/  r852_read_buf ; 
 int /*<<< orphan*/  r852_read_byte ; 
 int /*<<< orphan*/  r852_read_oob ; 
 int /*<<< orphan*/  r852_ready ; 
 int /*<<< orphan*/  r852_wait ; 
 int /*<<< orphan*/  r852_write_buf ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct r852_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int  r852_probe(struct pci_dev *pci_dev, const struct pci_device_id *id)
{
	int error;
	struct nand_chip *chip;
	struct r852_device *dev;

	/* pci initialization */
	error = pci_enable_device(pci_dev);

	if (error)
		goto error1;

	pci_set_master(pci_dev);

	error = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	if (error)
		goto error2;

	error = pci_request_regions(pci_dev, DRV_NAME);

	if (error)
		goto error3;

	error = -ENOMEM;

	/* init nand chip, but register it only on card insert */
	chip = kzalloc(sizeof(struct nand_chip), GFP_KERNEL);

	if (!chip)
		goto error4;

	/* commands */
	chip->legacy.cmd_ctrl = r852_cmdctl;
	chip->legacy.waitfunc = r852_wait;
	chip->legacy.dev_ready = r852_ready;

	/* I/O */
	chip->legacy.read_byte = r852_read_byte;
	chip->legacy.read_buf = r852_read_buf;
	chip->legacy.write_buf = r852_write_buf;

	/* ecc */
	chip->ecc.mode = NAND_ECC_HW_SYNDROME;
	chip->ecc.size = R852_DMA_LEN;
	chip->ecc.bytes = SM_OOB_SIZE;
	chip->ecc.strength = 2;
	chip->ecc.hwctl = r852_ecc_hwctl;
	chip->ecc.calculate = r852_ecc_calculate;
	chip->ecc.correct = r852_ecc_correct;

	/* TODO: hack */
	chip->ecc.read_oob = r852_read_oob;

	/* init our device structure */
	dev = kzalloc(sizeof(struct r852_device), GFP_KERNEL);

	if (!dev)
		goto error5;

	nand_set_controller_data(chip, dev);
	dev->chip = chip;
	dev->pci_dev = pci_dev;
	pci_set_drvdata(pci_dev, dev);

	dev->bounce_buffer = dma_alloc_coherent(&pci_dev->dev, R852_DMA_LEN,
		&dev->phys_bounce_buffer, GFP_KERNEL);

	if (!dev->bounce_buffer)
		goto error6;


	error = -ENODEV;
	dev->mmio = pci_ioremap_bar(pci_dev, 0);

	if (!dev->mmio)
		goto error7;

	error = -ENOMEM;
	dev->tmp_buffer = kzalloc(SM_SECTOR_SIZE, GFP_KERNEL);

	if (!dev->tmp_buffer)
		goto error8;

	init_completion(&dev->dma_done);

	dev->card_workqueue = create_freezable_workqueue(DRV_NAME);

	if (!dev->card_workqueue)
		goto error9;

	INIT_DELAYED_WORK(&dev->card_detect_work, r852_card_detect_work);

	/* shutdown everything - precation */
	r852_engine_disable(dev);
	r852_disable_irqs(dev);

	r852_dma_test(dev);

	dev->irq = pci_dev->irq;
	spin_lock_init(&dev->irqlock);

	dev->card_detected = 0;
	r852_card_update_present(dev);

	/*register irq handler*/
	error = -ENODEV;
	if (request_irq(pci_dev->irq, &r852_irq, IRQF_SHARED,
			  DRV_NAME, dev))
		goto error10;

	/* kick initial present test */
	queue_delayed_work(dev->card_workqueue,
		&dev->card_detect_work, 0);


	pr_notice("driver loaded successfully\n");
	return 0;

error10:
	destroy_workqueue(dev->card_workqueue);
error9:
	kfree(dev->tmp_buffer);
error8:
	pci_iounmap(pci_dev, dev->mmio);
error7:
	dma_free_coherent(&pci_dev->dev, R852_DMA_LEN, dev->bounce_buffer,
			  dev->phys_bounce_buffer);
error6:
	kfree(dev);
error5:
	kfree(chip);
error4:
	pci_release_regions(pci_dev);
error3:
error2:
	pci_disable_device(pci_dev);
error1:
	return error;
}