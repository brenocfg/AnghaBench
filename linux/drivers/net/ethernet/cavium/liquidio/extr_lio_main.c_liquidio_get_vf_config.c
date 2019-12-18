#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int id; scalar_t__ active; } ;
struct TYPE_7__ {int num_vfs_alloced; int* vf_vlantci; int /*<<< orphan*/ * vf_spoofchk; int /*<<< orphan*/ * vf_linkstate; TYPE_1__ trusted_vf; int /*<<< orphan*/ * vf_macaddr; } ;
struct octeon_device {TYPE_2__ sriov_info; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  speed; } ;
struct TYPE_9__ {TYPE_3__ s; } ;
struct TYPE_10__ {TYPE_4__ link; } ;
struct lio {TYPE_5__ linfo; struct octeon_device* oct_dev; } ;
struct ifla_vf_info {int vf; int vlan; int qos; int trusted; scalar_t__ min_tx_rate; int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  linkstate; int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 int EINVAL ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ifla_vf_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int liquidio_get_vf_config(struct net_device *netdev, int vfidx,
				  struct ifla_vf_info *ivi)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	u8 *macaddr;

	if (vfidx < 0 || vfidx >= oct->sriov_info.num_vfs_alloced)
		return -EINVAL;

	memset(ivi, 0, sizeof(struct ifla_vf_info));

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
	ivi->spoofchk = oct->sriov_info.vf_spoofchk[vfidx];
	ivi->max_tx_rate = lio->linfo.link.s.speed;
	ivi->min_tx_rate = 0;

	return 0;
}