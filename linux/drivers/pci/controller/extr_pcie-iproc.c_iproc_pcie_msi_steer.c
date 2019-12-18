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
struct iproc_pcie {int type; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IPROC_PCIE_PAXB_V2 129 
#define  IPROC_PCIE_PAXC_V2 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int iproc_pcie_paxb_v2_msi_steer (struct iproc_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_pcie_paxc_v2_msi_steer (struct iproc_pcie*,int /*<<< orphan*/ ,int) ; 
 int iproce_pcie_get_msi (struct iproc_pcie*,struct device_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iproc_pcie_msi_steer(struct iproc_pcie *pcie,
				struct device_node *msi_node)
{
	struct device *dev = pcie->dev;
	int ret;
	u64 msi_addr;

	ret = iproce_pcie_get_msi(pcie, msi_node, &msi_addr);
	if (ret < 0) {
		dev_err(dev, "msi steering failed\n");
		return ret;
	}

	switch (pcie->type) {
	case IPROC_PCIE_PAXB_V2:
		ret = iproc_pcie_paxb_v2_msi_steer(pcie, msi_addr);
		if (ret)
			return ret;
		break;
	case IPROC_PCIE_PAXC_V2:
		iproc_pcie_paxc_v2_msi_steer(pcie, msi_addr, true);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}