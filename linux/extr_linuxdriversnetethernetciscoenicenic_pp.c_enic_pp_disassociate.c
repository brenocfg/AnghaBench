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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct enic_port_profile {int /*<<< orphan*/  mac_addr; } ;
struct enic {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENIC_DEVCMD_PROXY_BY_INDEX (int,int,struct enic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENIC_PP_BY_INDEX (struct enic*,int,struct enic_port_profile*,int*) ; 
 int PORT_SELF_VF ; 
 int enic_unset_port_profile (struct enic*,int) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_del_addr ; 

__attribute__((used)) static int enic_pp_disassociate(struct enic *enic, int vf,
	struct enic_port_profile *prev_pp, int *restore_pp)
{
	struct net_device *netdev = enic->netdev;
	struct enic_port_profile *pp;
	int err;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	if (err)
		return err;

	/* Deregister mac addresses */
	if (!is_zero_ether_addr(pp->mac_addr))
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_del_addr,
			pp->mac_addr);
	else if (vf == PORT_SELF_VF && !is_zero_ether_addr(netdev->dev_addr))
		ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_del_addr,
			netdev->dev_addr);

	return enic_unset_port_profile(enic, vf);
}