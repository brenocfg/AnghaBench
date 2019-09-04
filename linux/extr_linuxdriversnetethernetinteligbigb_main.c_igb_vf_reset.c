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
typedef  size_t u32 ;
struct vf_data_storage {int pf_vlan; int pf_qos; scalar_t__ num_vf_mc_hashes; int /*<<< orphan*/  last_nack; int /*<<< orphan*/  flags; } ;
struct igb_adapter {int /*<<< orphan*/  netdev; struct vf_data_storage* vf_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGB_VF_FLAG_PF_SET_MAC ; 
 int VLAN_PRIO_SHIFT ; 
 int /*<<< orphan*/  igb_clear_vf_vfta (struct igb_adapter*,size_t) ; 
 int /*<<< orphan*/  igb_set_rx_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_set_vf_vlan (struct igb_adapter*,int,int,size_t) ; 
 int /*<<< orphan*/  igb_set_vf_vlan_strip (struct igb_adapter*,size_t,int) ; 
 int /*<<< orphan*/  igb_set_vmolr (struct igb_adapter*,size_t,int) ; 
 int /*<<< orphan*/  igb_set_vmvir (struct igb_adapter*,int,size_t) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static inline void igb_vf_reset(struct igb_adapter *adapter, u32 vf)
{
	struct vf_data_storage *vf_data = &adapter->vf_data[vf];

	/* clear flags - except flag that indicates PF has set the MAC */
	vf_data->flags &= IGB_VF_FLAG_PF_SET_MAC;
	vf_data->last_nack = jiffies;

	/* reset vlans for device */
	igb_clear_vf_vfta(adapter, vf);
	igb_set_vf_vlan(adapter, vf_data->pf_vlan, true, vf);
	igb_set_vmvir(adapter, vf_data->pf_vlan |
			       (vf_data->pf_qos << VLAN_PRIO_SHIFT), vf);
	igb_set_vmolr(adapter, vf, !vf_data->pf_vlan);
	igb_set_vf_vlan_strip(adapter, vf, !!(vf_data->pf_vlan));

	/* reset multicast table array for vf */
	adapter->vf_data[vf].num_vf_mc_hashes = 0;

	/* Flush and reset the mta with the new values */
	igb_set_rx_mode(adapter->netdev);
}