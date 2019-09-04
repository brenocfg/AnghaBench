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
typedef  int u64 ;
struct i40e_vsi {int /*<<< orphan*/  netdev; struct i40e_pf* back; } ;
struct i40e_pf {int dummy; } ;

/* Variables and functions */
 int I40E_FLEX_INDEX_ENTRIES ; 
 int I40E_L3_DST_MASK ; 
 int I40E_L3_SRC_MASK ; 
 int I40E_L4_DST_MASK ; 
 int I40E_L4_SRC_MASK ; 
 int I40E_VERIFY_TAG_MASK ; 
 int /*<<< orphan*/  drv ; 
 int i40e_pit_index_to_mask (int) ; 
 int /*<<< orphan*/  netif_info (struct i40e_pf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void i40e_print_input_set(struct i40e_vsi *vsi, u64 old, u64 new)
{
	struct i40e_pf *pf = vsi->back;
	bool old_value, new_value;
	int i;

	old_value = !!(old & I40E_L3_SRC_MASK);
	new_value = !!(new & I40E_L3_SRC_MASK);
	if (old_value != new_value)
		netif_info(pf, drv, vsi->netdev, "L3 source address: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	old_value = !!(old & I40E_L3_DST_MASK);
	new_value = !!(new & I40E_L3_DST_MASK);
	if (old_value != new_value)
		netif_info(pf, drv, vsi->netdev, "L3 destination address: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	old_value = !!(old & I40E_L4_SRC_MASK);
	new_value = !!(new & I40E_L4_SRC_MASK);
	if (old_value != new_value)
		netif_info(pf, drv, vsi->netdev, "L4 source port: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	old_value = !!(old & I40E_L4_DST_MASK);
	new_value = !!(new & I40E_L4_DST_MASK);
	if (old_value != new_value)
		netif_info(pf, drv, vsi->netdev, "L4 destination port: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	old_value = !!(old & I40E_VERIFY_TAG_MASK);
	new_value = !!(new & I40E_VERIFY_TAG_MASK);
	if (old_value != new_value)
		netif_info(pf, drv, vsi->netdev, "SCTP verification tag: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	/* Show change of flexible filter entries */
	for (i = 0; i < I40E_FLEX_INDEX_ENTRIES; i++) {
		u64 flex_mask = i40e_pit_index_to_mask(i);

		old_value = !!(old & flex_mask);
		new_value = !!(new & flex_mask);
		if (old_value != new_value)
			netif_info(pf, drv, vsi->netdev, "FLEX index %d: %s -> %s\n",
				   i,
				   old_value ? "ON" : "OFF",
				   new_value ? "ON" : "OFF");
	}

	netif_info(pf, drv, vsi->netdev, "  Current input set: %0llx\n",
		   old);
	netif_info(pf, drv, vsi->netdev, "Requested input set: %0llx\n",
		   new);
}