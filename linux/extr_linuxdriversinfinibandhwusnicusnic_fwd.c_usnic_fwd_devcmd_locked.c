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
struct usnic_fwd_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  lock; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
typedef  enum vnic_devcmd_cmd { ____Placeholder_vnic_devcmd_cmd } vnic_devcmd_cmd ;

/* Variables and functions */
 int CMD_DEL_FILTER ; 
 int ERR_EINVAL ; 
 int enic_api_devcmd_proxy_by_index (struct net_device*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_dbg (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int usnic_fwd_devcmd_locked(struct usnic_fwd_dev *ufdev, int vnic_idx,
					enum vnic_devcmd_cmd cmd, u64 *a0,
					u64 *a1)
{
	int status;
	struct net_device *netdev = ufdev->netdev;

	lockdep_assert_held(&ufdev->lock);

	status = enic_api_devcmd_proxy_by_index(netdev,
			vnic_idx,
			cmd,
			a0, a1,
			1000);
	if (status) {
		if (status == ERR_EINVAL && cmd == CMD_DEL_FILTER) {
			usnic_dbg("Dev %s vnic idx %u cmd %u already deleted",
					ufdev->name, vnic_idx, cmd);
		} else {
			usnic_err("Dev %s vnic idx %u cmd %u failed with status %d\n",
					ufdev->name, vnic_idx, cmd,
					status);
		}
	} else {
		usnic_dbg("Dev %s vnic idx %u cmd %u success",
				ufdev->name, vnic_idx, cmd);
	}

	return status;
}