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
typedef  int u32 ;
struct spa_data {int bdfn; int /*<<< orphan*/  phb_opal_id; } ;
struct pnv_phb {int /*<<< orphan*/  opal_id; } ;
struct pci_dev {int devfn; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (struct spa_data*) ; 
 struct spa_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int opal_npu_spa_setup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct pci_controller* pci_bus_to_host (TYPE_1__*) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

int pnv_ocxl_spa_setup(struct pci_dev *dev, void *spa_mem, int PE_mask,
		void **platform_data)
{
	struct pci_controller *hose = pci_bus_to_host(dev->bus);
	struct pnv_phb *phb = hose->private_data;
	struct spa_data *data;
	u32 bdfn;
	int rc;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	bdfn = (dev->bus->number << 8) | dev->devfn;
	rc = opal_npu_spa_setup(phb->opal_id, bdfn, virt_to_phys(spa_mem),
				PE_mask);
	if (rc) {
		dev_err(&dev->dev, "Can't setup Shared Process Area: %d\n", rc);
		kfree(data);
		return rc;
	}
	data->phb_opal_id = phb->opal_id;
	data->bdfn = bdfn;
	*platform_data = (void *) data;
	return 0;
}