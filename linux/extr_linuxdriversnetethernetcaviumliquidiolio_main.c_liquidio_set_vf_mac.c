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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int num_vfs_alloced; } ;
struct octeon_device {TYPE_1__ sriov_info; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int __liquidio_set_vf_mac (struct net_device*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cn23xx_tell_vf_its_macaddr_changed (struct octeon_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int liquidio_set_vf_mac(struct net_device *netdev, int vfidx, u8 *mac)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	int retval;

	if (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		return -EINVAL;

	retval = __liquidio_set_vf_mac(netdev, vfidx, mac, true);
	if (!retval)
		cn23xx_tell_vf_its_macaddr_changed(oct, vfidx, mac);

	return retval;
}