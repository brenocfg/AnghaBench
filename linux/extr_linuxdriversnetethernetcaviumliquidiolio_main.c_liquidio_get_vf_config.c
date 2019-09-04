#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int id; scalar_t__ active; } ;
struct TYPE_4__ {int num_vfs_alloced; int* vf_vlantci; int /*<<< orphan*/ * vf_linkstate; TYPE_1__ trusted_vf; int /*<<< orphan*/ * vf_macaddr; } ;
struct octeon_device {TYPE_2__ sriov_info; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct ifla_vf_info {int vf; int vlan; int qos; int trusted; int /*<<< orphan*/  linkstate; int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 int EINVAL ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int liquidio_get_vf_config(struct net_device *netdev, int vfidx,
				  struct ifla_vf_info *ivi)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	u8 *macaddr;

	if (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		return -EINVAL;

	ivi->vf = vfidx;
	macaddr = 2 + (u8 *)&oct->sriov_info.vf_macaddr[vfidx];
	ether_addr_copy(&ivi->mac[0], macaddr);
	ivi->vlan = oct->sriov_info.vf_vlantci[vfidx] & VLAN_VID_MASK;
	ivi->qos = oct->sriov_info.vf_vlantci[vfidx] >> VLAN_PRIO_SHIFT;
	if (oct->sriov_info.trusted_vf.active &&
	    oct->sriov_info.trusted_vf.id == vfidx)
		ivi->trusted = true;
	else
		ivi->trusted = false;
	ivi->linkstate = oct->sriov_info.vf_linkstate[vfidx];
	return 0;
}