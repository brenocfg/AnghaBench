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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct bnxt {int hwrm_spec_code; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FW_RESET_AP ; 
 int /*<<< orphan*/  BNXT_FW_RESET_CHIP ; 
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETH_RESET_ALL ; 
 scalar_t__ ETH_RESET_AP ; 
 int bnxt_firmware_reset (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 scalar_t__ pci_vfs_assigned (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_reset(struct net_device *dev, u32 *flags)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc = 0;

	if (!BNXT_PF(bp)) {
		netdev_err(dev, "Reset is not supported from a VF\n");
		return -EOPNOTSUPP;
	}

	if (pci_vfs_assigned(bp->pdev)) {
		netdev_err(dev,
			   "Reset not allowed when VFs are assigned to VMs\n");
		return -EBUSY;
	}

	if (*flags == ETH_RESET_ALL) {
		/* This feature is not supported in older firmware versions */
		if (bp->hwrm_spec_code < 0x10803)
			return -EOPNOTSUPP;

		rc = bnxt_firmware_reset(dev, BNXT_FW_RESET_CHIP);
		if (!rc) {
			netdev_info(dev, "Reset request successful. Reload driver to complete reset\n");
			*flags = 0;
		}
	} else if (*flags == ETH_RESET_AP) {
		/* This feature is not supported in older firmware versions */
		if (bp->hwrm_spec_code < 0x10803)
			return -EOPNOTSUPP;

		rc = bnxt_firmware_reset(dev, BNXT_FW_RESET_AP);
		if (!rc) {
			netdev_info(dev, "Reset Application Processor request successful.\n");
			*flags = 0;
		}
	} else {
		rc = -EINVAL;
	}

	return rc;
}