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
typedef  int /*<<< orphan*/  u16 ;
struct efx_nic {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  filter_sem; } ;
struct efx_ef10_filter_vlan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_ef10_filter_del_vlan_internal (struct efx_nic*,struct efx_ef10_filter_vlan*) ; 
 struct efx_ef10_filter_vlan* efx_ef10_filter_find_vlan (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rwsem_assert_write_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_ef10_filter_del_vlan(struct efx_nic *efx, u16 vid)
{
	struct efx_ef10_filter_vlan *vlan;

	/* See comment in efx_ef10_filter_table_remove() */
	if (!efx_rwsem_assert_write_locked(&efx->filter_sem))
		return;

	vlan = efx_ef10_filter_find_vlan(efx, vid);
	if (!vlan) {
		netif_err(efx, drv, efx->net_dev,
			  "VLAN %u not found in filter state\n", vid);
		return;
	}

	efx_ef10_filter_del_vlan_internal(efx, vlan);
}