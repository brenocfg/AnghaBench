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
typedef  scalar_t__ u64 ;
struct resource {scalar_t__ start; } ;
struct iproc_pcie {struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ GITS_TRANSLATER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static int iproce_pcie_get_msi(struct iproc_pcie *pcie,
			       struct device_node *msi_node,
			       u64 *msi_addr)
{
	struct device *dev = pcie->dev;
	int ret;
	struct resource res;

	/*
	 * Check if 'msi-map' points to ARM GICv3 ITS, which is the only
	 * supported external MSI controller that requires steering.
	 */
	if (!of_device_is_compatible(msi_node, "arm,gic-v3-its")) {
		dev_err(dev, "unable to find compatible MSI controller\n");
		return -ENODEV;
	}

	/* derive GITS_TRANSLATER address from GICv3 */
	ret = of_address_to_resource(msi_node, 0, &res);
	if (ret < 0) {
		dev_err(dev, "unable to obtain MSI controller resources\n");
		return ret;
	}

	*msi_addr = res.start + GITS_TRANSLATER;
	return 0;
}