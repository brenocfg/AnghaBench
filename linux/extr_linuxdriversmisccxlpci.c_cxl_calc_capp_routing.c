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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_capp_unit_id (struct device_node*,int /*<<< orphan*/ ) ; 
 int get_phb_index (struct device_node*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* pnv_pci_get_phb_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int cxl_calc_capp_routing(struct pci_dev *dev, u64 *chipid,
			     u32 *phb_index, u64 *capp_unit_id)
{
	int rc;
	struct device_node *np;
	const __be32 *prop;

	if (!(np = pnv_pci_get_phb_node(dev)))
		return -ENODEV;

	while (np && !(prop = of_get_property(np, "ibm,chip-id", NULL)))
		np = of_get_next_parent(np);
	if (!np)
		return -ENODEV;

	*chipid = be32_to_cpup(prop);

	rc = get_phb_index(np, phb_index);
	if (rc) {
		pr_err("cxl: invalid phb index\n");
		return rc;
	}

	*capp_unit_id = get_capp_unit_id(np, *phb_index);
	of_node_put(np);
	if (!*capp_unit_id) {
		pr_err("cxl: invalid capp unit id (phb_index: %d)\n",
		       *phb_index);
		return -ENODEV;
	}

	return 0;
}