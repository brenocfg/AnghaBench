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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ice_vsi {int /*<<< orphan*/  tmp_sync_list; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ice_add_mac_to_list (struct ice_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ice_add_mac_to_sync_list(struct net_device *netdev, const u8 *addr)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;

	if (ice_add_mac_to_list(vsi, &vsi->tmp_sync_list, addr))
		return -EINVAL;

	return 0;
}