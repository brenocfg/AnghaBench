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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  netif_is_vxlan (struct net_device const*) ; 
 int /*<<< orphan*/  vxlan_fdb_clear_offload (struct net_device const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_nve_vxlan_clear_offload(const struct net_device *nve_dev, __be32 vni)
{
	if (WARN_ON(!netif_is_vxlan(nve_dev)))
		return;
	vxlan_fdb_clear_offload(nve_dev, vni);
}