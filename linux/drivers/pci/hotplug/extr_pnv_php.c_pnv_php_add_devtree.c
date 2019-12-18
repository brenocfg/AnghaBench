#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pnv_php_slot {TYPE_1__* dn; int /*<<< orphan*/  ocs; void* dt; void* fdt; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * child; int /*<<< orphan*/  phandle; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fdt_totalsize (void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_changeset_apply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_changeset_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_changeset_init (int /*<<< orphan*/ *) ; 
 void* of_fdt_unflatten_tree (void*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_warn (int /*<<< orphan*/ ,char*,...) ; 
 int pnv_pci_get_device_tree (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pnv_php_add_pdns (struct pnv_php_slot*) ; 
 int pnv_php_populate_changeset (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pnv_php_reverse_nodes (TYPE_1__*) ; 

__attribute__((used)) static int pnv_php_add_devtree(struct pnv_php_slot *php_slot)
{
	void *fdt, *fdt1, *dt;
	int ret;

	/* We don't know the FDT blob size. We try to get it through
	 * maximal memory chunk and then copy it to another chunk that
	 * fits the real size.
	 */
	fdt1 = kzalloc(0x10000, GFP_KERNEL);
	if (!fdt1) {
		ret = -ENOMEM;
		goto out;
	}

	ret = pnv_pci_get_device_tree(php_slot->dn->phandle, fdt1, 0x10000);
	if (ret) {
		pci_warn(php_slot->pdev, "Error %d getting FDT blob\n", ret);
		goto free_fdt1;
	}

	fdt = kmemdup(fdt1, fdt_totalsize(fdt1), GFP_KERNEL);
	if (!fdt) {
		ret = -ENOMEM;
		goto free_fdt1;
	}

	/* Unflatten device tree blob */
	dt = of_fdt_unflatten_tree(fdt, php_slot->dn, NULL);
	if (!dt) {
		ret = -EINVAL;
		pci_warn(php_slot->pdev, "Cannot unflatten FDT\n");
		goto free_fdt;
	}

	/* Initialize and apply the changeset */
	of_changeset_init(&php_slot->ocs);
	pnv_php_reverse_nodes(php_slot->dn);
	ret = pnv_php_populate_changeset(&php_slot->ocs, php_slot->dn);
	if (ret) {
		pnv_php_reverse_nodes(php_slot->dn);
		pci_warn(php_slot->pdev, "Error %d populating changeset\n",
			 ret);
		goto free_dt;
	}

	php_slot->dn->child = NULL;
	ret = of_changeset_apply(&php_slot->ocs);
	if (ret) {
		pci_warn(php_slot->pdev, "Error %d applying changeset\n", ret);
		goto destroy_changeset;
	}

	/* Add device node firmware data */
	pnv_php_add_pdns(php_slot);
	php_slot->fdt = fdt;
	php_slot->dt  = dt;
	kfree(fdt1);
	goto out;

destroy_changeset:
	of_changeset_destroy(&php_slot->ocs);
free_dt:
	kfree(dt);
	php_slot->dn->child = NULL;
free_fdt:
	kfree(fdt);
free_fdt1:
	kfree(fdt1);
out:
	return ret;
}