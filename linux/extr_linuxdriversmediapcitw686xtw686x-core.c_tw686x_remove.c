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
struct tw686x_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/ * pci_dev; int /*<<< orphan*/  mmio; int /*<<< orphan*/  dma_delay_timer; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tw686x_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct tw686x_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tw686x_audio_free (struct tw686x_dev*) ; 
 int /*<<< orphan*/  tw686x_video_free (struct tw686x_dev*) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tw686x_remove(struct pci_dev *pci_dev)
{
	struct tw686x_dev *dev = pci_get_drvdata(pci_dev);
	unsigned long flags;

	/* This guarantees the IRQ handler is no longer running,
	 * which means we can kiss good-bye some resources.
	 */
	free_irq(pci_dev->irq, dev);

	tw686x_video_free(dev);
	tw686x_audio_free(dev);
	del_timer_sync(&dev->dma_delay_timer);

	pci_iounmap(pci_dev, dev->mmio);
	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);

	/*
	 * Setting pci_dev to NULL allows to detect hardware is no longer
	 * available and will be used by vb2_ops. This is required because
	 * the device sometimes hot-unplugs itself as the result of a PCIe
	 * link down.
	 * The lock is really important here.
	 */
	spin_lock_irqsave(&dev->lock, flags);
	dev->pci_dev = NULL;
	spin_unlock_irqrestore(&dev->lock, flags);

	/*
	 * This calls tw686x_dev_release if it's the last reference.
	 * Otherwise, release is postponed until there are no users left.
	 */
	v4l2_device_put(&dev->v4l2_dev);
}