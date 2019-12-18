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
typedef  int /*<<< orphan*/  u32 ;
struct iproc_pcie {scalar_t__ need_msi_steer; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int iproc_msi_init (struct iproc_pcie*,struct device_node*) ; 
 int iproc_pcie_msi_steer (struct iproc_pcie*,struct device_node*) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iproc_pcie_msi_enable(struct iproc_pcie *pcie)
{
	struct device_node *msi_node;
	int ret;

	/*
	 * Either the "msi-parent" or the "msi-map" phandle needs to exist
	 * for us to obtain the MSI node.
	 */

	msi_node = of_parse_phandle(pcie->dev->of_node, "msi-parent", 0);
	if (!msi_node) {
		const __be32 *msi_map = NULL;
		int len;
		u32 phandle;

		msi_map = of_get_property(pcie->dev->of_node, "msi-map", &len);
		if (!msi_map)
			return -ENODEV;

		phandle = be32_to_cpup(msi_map + 1);
		msi_node = of_find_node_by_phandle(phandle);
		if (!msi_node)
			return -ENODEV;
	}

	/*
	 * Certain revisions of the iProc PCIe controller require additional
	 * configurations to steer the MSI writes towards an external MSI
	 * controller.
	 */
	if (pcie->need_msi_steer) {
		ret = iproc_pcie_msi_steer(pcie, msi_node);
		if (ret)
			goto out_put_node;
	}

	/*
	 * If another MSI controller is being used, the call below should fail
	 * but that is okay
	 */
	ret = iproc_msi_init(pcie, msi_node);

out_put_node:
	of_node_put(msi_node);
	return ret;
}