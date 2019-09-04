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
struct TYPE_5__ {int active; int id; } ;
struct TYPE_6__ {int num_vfs_alloced; TYPE_2__ trusted_vf; } ;
struct TYPE_4__ {int /*<<< orphan*/  liquidio_firmware_version; } ;
struct octeon_device {TYPE_3__ sriov_info; TYPE_1__ fw_info; } ;
struct net_device {int dummy; } ;
struct lio {int /*<<< orphan*/  netdev; struct octeon_device* oct_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  liquidio_send_vf_trust_cmd (struct lio*,int,int) ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int liquidio_set_vf_trust(struct net_device *netdev, int vfidx,
				 bool setting)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;

	if (strcmp(oct->fw_info.liquidio_firmware_version, "1.7.1") < 0) {
		/* trusted vf is not supported by firmware older than 1.7.1 */
		return -EOPNOTSUPP;
	}

	if (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced) {
		netif_info(lio, drv, lio->netdev, "Invalid vfidx %d\n", vfidx);
		return -EINVAL;
	}

	if (setting) {
		/* Set */

		if (oct->sriov_info.trusted_vf.active &&
		    oct->sriov_info.trusted_vf.id == vfidx)
			return 0;

		if (oct->sriov_info.trusted_vf.active) {
			netif_info(lio, drv, lio->netdev, "More than one trusted VF is not allowed\n");
			return -EPERM;
		}
	} else {
		/* Clear */

		if (!oct->sriov_info.trusted_vf.active)
			return 0;
	}

	if (!liquidio_send_vf_trust_cmd(lio, vfidx, setting)) {
		if (setting) {
			oct->sriov_info.trusted_vf.id = vfidx;
			oct->sriov_info.trusted_vf.active = true;
		} else {
			oct->sriov_info.trusted_vf.active = false;
		}

		netif_info(lio, drv, lio->netdev, "VF %u is %strusted\n", vfidx,
			   setting ? "" : "not ");
	} else {
		netif_info(lio, drv, lio->netdev, "Failed to set VF trusted\n");
		return -1;
	}

	return 0;
}