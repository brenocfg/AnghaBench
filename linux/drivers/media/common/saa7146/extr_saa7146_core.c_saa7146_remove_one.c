#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_handle; int /*<<< orphan*/ * cpu_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_handle; int /*<<< orphan*/ * cpu_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_handle; int /*<<< orphan*/ * cpu_addr; } ;
struct saa7146_dev {int /*<<< orphan*/  mem; TYPE_4__* ext; TYPE_3__ d_rps0; TYPE_2__ d_rps1; TYPE_1__ d_i2c; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* detach ) (struct saa7146_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*,struct saa7146_dev*) ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  SAA7146_RPS_MEM ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct saa7146_dev*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct saa7146_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct v4l2_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_num ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct saa7146_dev*) ; 
 struct saa7146_dev* to_saa7146_dev (struct v4l2_device*) ; 

__attribute__((used)) static void saa7146_remove_one(struct pci_dev *pdev)
{
	struct v4l2_device *v4l2_dev = pci_get_drvdata(pdev);
	struct saa7146_dev *dev = to_saa7146_dev(v4l2_dev);
	struct {
		void *addr;
		dma_addr_t dma;
	} dev_map[] = {
		{ dev->d_i2c.cpu_addr, dev->d_i2c.dma_handle },
		{ dev->d_rps1.cpu_addr, dev->d_rps1.dma_handle },
		{ dev->d_rps0.cpu_addr, dev->d_rps0.dma_handle },
		{ NULL, 0 }
	}, *p;

	DEB_EE("dev:%p\n", dev);

	dev->ext->detach(dev);

	/* shut down all video dma transfers */
	saa7146_write(dev, MC1, 0x00ff0000);

	/* disable all irqs, release irq-routine */
	saa7146_write(dev, IER, 0);

	free_irq(pdev->irq, dev);

	for (p = dev_map; p->addr; p++)
		pci_free_consistent(pdev, SAA7146_RPS_MEM, p->addr, p->dma);

	iounmap(dev->mem);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
	kfree(dev);

	saa7146_num--;
}