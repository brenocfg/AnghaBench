#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sm501_devdata {struct sm501_devdata* regs_claim; int /*<<< orphan*/  regs; TYPE_1__* io_res; TYPE_1__* mem_res; int /*<<< orphan*/  irq; TYPE_3__* dev; scalar_t__ pdev_id; int /*<<< orphan*/ * platdata; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * platform_data; } ;
struct pci_dev {TYPE_3__ dev; TYPE_1__* resource; int /*<<< orphan*/  irq; scalar_t__ devfn; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  SM501_FBPD_SWAP_FB_ENDIAN ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  kfree (struct sm501_devdata*) ; 
 struct sm501_devdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct sm501_devdata*) ; 
 int /*<<< orphan*/  release_resource (struct sm501_devdata*) ; 
 struct sm501_devdata* request_mem_region (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_2__ sm501_fb_pdata ; 
 int /*<<< orphan*/  sm501_init_dev (struct sm501_devdata*) ; 
 int /*<<< orphan*/  sm501_pci_platdata ; 

__attribute__((used)) static int sm501_pci_probe(struct pci_dev *dev,
				     const struct pci_device_id *id)
{
	struct sm501_devdata *sm;
	int err;

	sm = kzalloc(sizeof(*sm), GFP_KERNEL);
	if (!sm) {
		err = -ENOMEM;
		goto err1;
	}

	/* set a default set of platform data */
	dev->dev.platform_data = sm->platdata = &sm501_pci_platdata;

	/* set a hopefully unique id for our child platform devices */
	sm->pdev_id = 32 + dev->devfn;

	pci_set_drvdata(dev, sm);

	err = pci_enable_device(dev);
	if (err) {
		dev_err(&dev->dev, "cannot enable device\n");
		goto err2;
	}

	sm->dev = &dev->dev;
	sm->irq = dev->irq;

#ifdef __BIG_ENDIAN
	/* if the system is big-endian, we most probably have a
	 * translation in the IO layer making the PCI bus little endian
	 * so make the framebuffer swapped pixels */

	sm501_fb_pdata.flags |= SM501_FBPD_SWAP_FB_ENDIAN;
#endif

	/* check our resources */

	if (!(pci_resource_flags(dev, 0) & IORESOURCE_MEM)) {
		dev_err(&dev->dev, "region #0 is not memory?\n");
		err = -EINVAL;
		goto err3;
	}

	if (!(pci_resource_flags(dev, 1) & IORESOURCE_MEM)) {
		dev_err(&dev->dev, "region #1 is not memory?\n");
		err = -EINVAL;
		goto err3;
	}

	/* make our resources ready for sharing */

	sm->io_res = &dev->resource[1];
	sm->mem_res = &dev->resource[0];

	sm->regs_claim = request_mem_region(sm->io_res->start,
					    0x100, "sm501");
	if (!sm->regs_claim) {
		dev_err(&dev->dev, "cannot claim registers\n");
		err= -EBUSY;
		goto err3;
	}

	sm->regs = pci_ioremap_bar(dev, 1);
	if (!sm->regs) {
		dev_err(&dev->dev, "cannot remap registers\n");
		err = -EIO;
		goto err4;
	}

	sm501_init_dev(sm);
	return 0;

 err4:
	release_resource(sm->regs_claim);
	kfree(sm->regs_claim);
 err3:
	pci_disable_device(dev);
 err2:
	kfree(sm);
 err1:
	return err;
}