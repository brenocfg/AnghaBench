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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOENT ; 
 unsigned int PAGE_SIZE ; 
 unsigned long alloc_xen_mmio (unsigned int) ; 
 int /*<<< orphan*/  callback_via ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  get_callback_via (struct pci_dev*) ; 
 int /*<<< orphan*/  gnttab_free_auto_xlat_frames () ; 
 int gnttab_init () ; 
 unsigned int gnttab_max_grant_frames () ; 
 int gnttab_setup_auto_xlat_frames (unsigned long) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int pci_request_region (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 long pci_resource_len (struct pci_dev*,int) ; 
 long pci_resource_start (struct pci_dev*,int) ; 
 long platform_mmio ; 
 long platform_mmiolen ; 
 int xen_allocate_irq (struct pci_dev*) ; 
 int /*<<< orphan*/  xen_domain () ; 
 int /*<<< orphan*/  xen_have_vector_callback ; 
 int xen_set_callback_via (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_probe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int platform_pci_probe(struct pci_dev *pdev,
			      const struct pci_device_id *ent)
{
	int i, ret;
	long ioaddr;
	long mmio_addr, mmio_len;
	unsigned int max_nr_gframes;
	unsigned long grant_frames;

	if (!xen_domain())
		return -ENODEV;

	i = pci_enable_device(pdev);
	if (i)
		return i;

	ioaddr = pci_resource_start(pdev, 0);

	mmio_addr = pci_resource_start(pdev, 1);
	mmio_len = pci_resource_len(pdev, 1);

	if (mmio_addr == 0 || ioaddr == 0) {
		dev_err(&pdev->dev, "no resources found\n");
		ret = -ENOENT;
		goto pci_out;
	}

	ret = pci_request_region(pdev, 1, DRV_NAME);
	if (ret < 0)
		goto pci_out;

	ret = pci_request_region(pdev, 0, DRV_NAME);
	if (ret < 0)
		goto mem_out;

	platform_mmio = mmio_addr;
	platform_mmiolen = mmio_len;
	if (!xen_have_vector_callback) {
		ret = xen_allocate_irq(pdev);
		if (ret) {
			dev_warn(&pdev->dev, "request_irq failed err=%d\n", ret);
			goto out;
		}
		callback_via = get_callback_via(pdev);
		ret = xen_set_callback_via(callback_via);
		if (ret) {
			dev_warn(&pdev->dev, "Unable to set the evtchn callback "
					 "err=%d\n", ret);
			goto out;
		}
	}

	max_nr_gframes = gnttab_max_grant_frames();
	grant_frames = alloc_xen_mmio(PAGE_SIZE * max_nr_gframes);
	ret = gnttab_setup_auto_xlat_frames(grant_frames);
	if (ret)
		goto out;
	ret = gnttab_init();
	if (ret)
		goto grant_out;
	xenbus_probe(NULL);
	return 0;
grant_out:
	gnttab_free_auto_xlat_frames();
out:
	pci_release_region(pdev, 0);
mem_out:
	pci_release_region(pdev, 1);
pci_out:
	pci_disable_device(pdev);
	return ret;
}