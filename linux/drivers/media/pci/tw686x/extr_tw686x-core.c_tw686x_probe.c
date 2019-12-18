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
struct TYPE_2__ {int /*<<< orphan*/  release; } ;
struct tw686x_dev {struct tw686x_dev* video_channels; struct tw686x_dev* audio_channels; int /*<<< orphan*/  mmio; TYPE_1__ v4l2_dev; int /*<<< orphan*/  dma_delay_timer; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; struct pci_dev* pci_dev; int /*<<< orphan*/  dma_mode; int /*<<< orphan*/  type; } ;
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int device; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_CHANNEL_ENABLE ; 
 int /*<<< orphan*/  DMA_CHANNEL_TIMEOUT ; 
 int /*<<< orphan*/  DMA_CMD ; 
 int /*<<< orphan*/  DMA_CONFIG ; 
 int /*<<< orphan*/  DMA_TIMER_INTERVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/ * SRST ; 
 int /*<<< orphan*/  SYS_SOFT_RST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int dma_interval ; 
 int /*<<< orphan*/  dma_mode ; 
 int /*<<< orphan*/  dma_mode_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tw686x_dev*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tw686x_dev*) ; 
 struct tw686x_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max_channels (struct tw686x_dev*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct tw686x_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct tw686x_dev*,int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tw686x_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tw686x_audio_init (struct tw686x_dev*) ; 
 int /*<<< orphan*/  tw686x_dev_release ; 
 int /*<<< orphan*/  tw686x_dma_delay ; 
 int /*<<< orphan*/  tw686x_irq ; 
 int tw686x_video_init (struct tw686x_dev*) ; 

__attribute__((used)) static int tw686x_probe(struct pci_dev *pci_dev,
			const struct pci_device_id *pci_id)
{
	struct tw686x_dev *dev;
	int err;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;
	dev->type = pci_id->driver_data;
	dev->dma_mode = dma_mode;
	sprintf(dev->name, "tw%04X", pci_dev->device);

	dev->video_channels = kcalloc(max_channels(dev),
		sizeof(*dev->video_channels), GFP_KERNEL);
	if (!dev->video_channels) {
		err = -ENOMEM;
		goto free_dev;
	}

	dev->audio_channels = kcalloc(max_channels(dev),
		sizeof(*dev->audio_channels), GFP_KERNEL);
	if (!dev->audio_channels) {
		err = -ENOMEM;
		goto free_video;
	}

	pr_info("%s: PCI %s, IRQ %d, MMIO 0x%lx (%s mode)\n", dev->name,
		pci_name(pci_dev), pci_dev->irq,
		(unsigned long)pci_resource_start(pci_dev, 0),
		dma_mode_name(dma_mode));

	dev->pci_dev = pci_dev;
	if (pci_enable_device(pci_dev)) {
		err = -EIO;
		goto free_audio;
	}

	pci_set_master(pci_dev);
	err = pci_set_dma_mask(pci_dev, DMA_BIT_MASK(32));
	if (err) {
		dev_err(&pci_dev->dev, "32-bit PCI DMA not supported\n");
		err = -EIO;
		goto disable_pci;
	}

	err = pci_request_regions(pci_dev, dev->name);
	if (err) {
		dev_err(&pci_dev->dev, "unable to request PCI region\n");
		goto disable_pci;
	}

	dev->mmio = pci_ioremap_bar(pci_dev, 0);
	if (!dev->mmio) {
		dev_err(&pci_dev->dev, "unable to remap PCI region\n");
		err = -ENOMEM;
		goto free_region;
	}

	/* Reset all subsystems */
	reg_write(dev, SYS_SOFT_RST, 0x0f);
	mdelay(1);

	reg_write(dev, SRST[0], 0x3f);
	if (max_channels(dev) > 4)
		reg_write(dev, SRST[1], 0x3f);

	/* Disable the DMA engine */
	reg_write(dev, DMA_CMD, 0);
	reg_write(dev, DMA_CHANNEL_ENABLE, 0);

	/* Enable DMA FIFO overflow and pointer check */
	reg_write(dev, DMA_CONFIG, 0xffffff04);
	reg_write(dev, DMA_CHANNEL_TIMEOUT, 0x140c8584);
	reg_write(dev, DMA_TIMER_INTERVAL, dma_interval);

	spin_lock_init(&dev->lock);

	err = request_irq(pci_dev->irq, tw686x_irq, IRQF_SHARED,
			  dev->name, dev);
	if (err < 0) {
		dev_err(&pci_dev->dev, "unable to request interrupt\n");
		goto iounmap;
	}

	timer_setup(&dev->dma_delay_timer, tw686x_dma_delay, 0);

	/*
	 * This must be set right before initializing v4l2_dev.
	 * It's used to release resources after the last handle
	 * held is released.
	 */
	dev->v4l2_dev.release = tw686x_dev_release;
	err = tw686x_video_init(dev);
	if (err) {
		dev_err(&pci_dev->dev, "can't register video\n");
		goto free_irq;
	}

	err = tw686x_audio_init(dev);
	if (err)
		dev_warn(&pci_dev->dev, "can't register audio\n");

	pci_set_drvdata(pci_dev, dev);
	return 0;

free_irq:
	free_irq(pci_dev->irq, dev);
iounmap:
	pci_iounmap(pci_dev, dev->mmio);
free_region:
	pci_release_regions(pci_dev);
disable_pci:
	pci_disable_device(pci_dev);
free_audio:
	kfree(dev->audio_channels);
free_video:
	kfree(dev->video_channels);
free_dev:
	kfree(dev);
	return err;
}