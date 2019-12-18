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
struct efx_nic {int /*<<< orphan*/  filter_sem; } ;
struct efx_ef10_filter_vlan {scalar_t__* uc; scalar_t__* mc; scalar_t__* default_filters; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ EFX_EF10_FILTER_ID_INVALID ; 
 unsigned int EFX_EF10_NUM_DEFAULT_FILTERS ; 
 int /*<<< orphan*/  EFX_FILTER_PRI_AUTO ; 
 int /*<<< orphan*/  efx_ef10_filter_remove_unsafe (struct efx_nic*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  efx_rwsem_assert_write_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct efx_ef10_filter_vlan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_ef10_filter_del_vlan_internal(struct efx_nic *efx,
					      struct efx_ef10_filter_vlan *vlan)
{
	unsigned int i;

	/* See comment in efx_ef10_filter_table_remove() */
	if (!efx_rwsem_assert_write_locked(&efx->filter_sem))
		return;

	list_del(&vlan->list);

	for (i = 0; i < ARRAY_SIZE(vlan->uc); i++)
		efx_ef10_filter_remove_unsafe(efx, EFX_FILTER_PRI_AUTO,
					      vlan->uc[i]);
	for (i = 0; i < ARRAY_SIZE(vlan->mc); i++)
		efx_ef10_filter_remove_unsafe(efx, EFX_FILTER_PRI_AUTO,
					      vlan->mc[i]);
	for (i = 0; i < EFX_EF10_NUM_DEFAULT_FILTERS; i++)
		if (vlan->default_filters[i] != EFX_EF10_FILTER_ID_INVALID)
			efx_ef10_filter_remove_unsafe(efx, EFX_FILTER_PRI_AUTO,
						      vlan->default_filters[i]);

	kfree(vlan);
}