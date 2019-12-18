#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int handle; } ;
struct tc_cls_u32_offload {TYPE_1__ knode; } ;
struct ixgbe_jump_table {int link_hdl; struct ixgbe_jump_table* mask; struct ixgbe_jump_table* input; int /*<<< orphan*/  child_loc_map; } ;
struct ixgbe_adapter {int /*<<< orphan*/  fdir_perfect_lock; struct ixgbe_jump_table** jump_tables; } ;

/* Variables and functions */
 int EINVAL ; 
 int IXGBE_MAX_HW_ENTRIES ; 
 int IXGBE_MAX_LINK_HANDLE ; 
 int TC_U32_USERHTID (int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int ixgbe_update_ethtool_fdir_entry (struct ixgbe_adapter*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct ixgbe_jump_table*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_delete_clsu32(struct ixgbe_adapter *adapter,
			       struct tc_cls_u32_offload *cls)
{
	u32 hdl = cls->knode.handle;
	u32 uhtid = TC_U32_USERHTID(cls->knode.handle);
	u32 loc = cls->knode.handle & 0xfffff;
	int err = 0, i, j;
	struct ixgbe_jump_table *jump = NULL;

	if (loc > IXGBE_MAX_HW_ENTRIES)
		return -EINVAL;

	if ((uhtid != 0x800) && (uhtid >= IXGBE_MAX_LINK_HANDLE))
		return -EINVAL;

	/* Clear this filter in the link data it is associated with */
	if (uhtid != 0x800) {
		jump = adapter->jump_tables[uhtid];
		if (!jump)
			return -EINVAL;
		if (!test_bit(loc - 1, jump->child_loc_map))
			return -EINVAL;
		clear_bit(loc - 1, jump->child_loc_map);
	}

	/* Check if the filter being deleted is a link */
	for (i = 1; i < IXGBE_MAX_LINK_HANDLE; i++) {
		jump = adapter->jump_tables[i];
		if (jump && jump->link_hdl == hdl) {
			/* Delete filters in the hardware in the child hash
			 * table associated with this link
			 */
			for (j = 0; j < IXGBE_MAX_HW_ENTRIES; j++) {
				if (!test_bit(j, jump->child_loc_map))
					continue;
				spin_lock(&adapter->fdir_perfect_lock);
				err = ixgbe_update_ethtool_fdir_entry(adapter,
								      NULL,
								      j + 1);
				spin_unlock(&adapter->fdir_perfect_lock);
				clear_bit(j, jump->child_loc_map);
			}
			/* Remove resources for this link */
			kfree(jump->input);
			kfree(jump->mask);
			kfree(jump);
			adapter->jump_tables[i] = NULL;
			return err;
		}
	}

	spin_lock(&adapter->fdir_perfect_lock);
	err = ixgbe_update_ethtool_fdir_entry(adapter, NULL, loc);
	spin_unlock(&adapter->fdir_perfect_lock);
	return err;
}