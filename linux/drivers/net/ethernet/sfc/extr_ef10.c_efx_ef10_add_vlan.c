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
typedef  scalar_t__ u16 ;
struct efx_nic {int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  filter_sem; scalar_t__ filter_state; int /*<<< orphan*/  net_dev; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_vlan {int /*<<< orphan*/  list; scalar_t__ vid; } ;
struct efx_ef10_nic_data {int /*<<< orphan*/  vlan_lock; int /*<<< orphan*/  vlan_list; } ;

/* Variables and functions */
 int EALREADY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int efx_ef10_filter_add_vlan (struct efx_nic*,scalar_t__) ; 
 struct efx_ef10_vlan* efx_ef10_find_vlan (struct efx_nic*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct efx_ef10_vlan*) ; 
 struct efx_ef10_vlan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_add_vlan(struct efx_nic *efx, u16 vid)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	struct efx_ef10_vlan *vlan;
	int rc;

	mutex_lock(&nic_data->vlan_lock);

	vlan = efx_ef10_find_vlan(efx, vid);
	if (vlan) {
		/* We add VID 0 on init. 8021q adds it on module init
		 * for all interfaces with VLAN filtring feature.
		 */
		if (vid == 0)
			goto done_unlock;
		netif_warn(efx, drv, efx->net_dev,
			   "VLAN %u already added\n", vid);
		rc = -EALREADY;
		goto fail_exist;
	}

	rc = -ENOMEM;
	vlan = kzalloc(sizeof(*vlan), GFP_KERNEL);
	if (!vlan)
		goto fail_alloc;

	vlan->vid = vid;

	list_add_tail(&vlan->list, &nic_data->vlan_list);

	if (efx->filter_state) {
		mutex_lock(&efx->mac_lock);
		down_write(&efx->filter_sem);
		rc = efx_ef10_filter_add_vlan(efx, vlan->vid);
		up_write(&efx->filter_sem);
		mutex_unlock(&efx->mac_lock);
		if (rc)
			goto fail_filter_add_vlan;
	}

done_unlock:
	mutex_unlock(&nic_data->vlan_lock);
	return 0;

fail_filter_add_vlan:
	list_del(&vlan->list);
	kfree(vlan);
fail_alloc:
fail_exist:
	mutex_unlock(&nic_data->vlan_lock);
	return rc;
}