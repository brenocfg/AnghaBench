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
struct TYPE_2__ {scalar_t__ virt; } ;
struct vr_nor_mtd {scalar_t__ csr_base; TYPE_1__ map; int /*<<< orphan*/  info; struct pci_dev* dev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 scalar_t__ EXP_TIMING_CS0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int TIMING_WR_EN ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct vr_nor_mtd*) ; 
 struct vr_nor_mtd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct vr_nor_mtd*) ; 
 unsigned int readl (scalar_t__) ; 
 int vr_nor_init_maps (struct vr_nor_mtd*) ; 
 int vr_nor_init_partitions (struct vr_nor_mtd*) ; 
 int vr_nor_mtd_setup (struct vr_nor_mtd*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int vr_nor_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct vr_nor_mtd *p = NULL;
	unsigned int exp_timing_cs0;
	int err;

	err = pci_enable_device(dev);
	if (err)
		goto out;

	err = pci_request_regions(dev, DRV_NAME);
	if (err)
		goto disable_dev;

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	err = -ENOMEM;
	if (!p)
		goto release;

	p->dev = dev;

	err = vr_nor_init_maps(p);
	if (err)
		goto release;

	err = vr_nor_mtd_setup(p);
	if (err)
		goto destroy_maps;

	err = vr_nor_init_partitions(p);
	if (err)
		goto destroy_mtd_setup;

	pci_set_drvdata(dev, p);

	return 0;

      destroy_mtd_setup:
	map_destroy(p->info);

      destroy_maps:
	/* write-protect the flash bank */
	exp_timing_cs0 = readl(p->csr_base + EXP_TIMING_CS0);
	exp_timing_cs0 &= ~TIMING_WR_EN;
	writel(exp_timing_cs0, p->csr_base + EXP_TIMING_CS0);

	/* unmap the flash window */
	iounmap(p->map.virt);

	/* unmap the csr window */
	iounmap(p->csr_base);

      release:
	kfree(p);
	pci_release_regions(dev);

      disable_dev:
	pci_disable_device(dev);

      out:
	return err;
}