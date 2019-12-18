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
typedef  int u32 ;
struct ixgb_hw {int num_mc_addrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int ETH_ALEN ; 
 int IXGB_MC_TBL_SIZE ; 
 int IXGB_RAR_ENTRIES ; 
 int /*<<< orphan*/  IXGB_WRITE_REG_ARRAY (struct ixgb_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTA ; 
 int /*<<< orphan*/  RA ; 
 int ixgb_hash_mc_addr (struct ixgb_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgb_mta_set (struct ixgb_hw*,int) ; 
 int /*<<< orphan*/  ixgb_rar_set (struct ixgb_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

void
ixgb_mc_addr_list_update(struct ixgb_hw *hw,
			  u8 *mc_addr_list,
			  u32 mc_addr_count,
			  u32 pad)
{
	u32 hash_value;
	u32 i;
	u32 rar_used_count = 1;		/* RAR[0] is used for our MAC address */
	u8 *mca;

	ENTER();

	/* Set the new number of MC addresses that we are being requested to use. */
	hw->num_mc_addrs = mc_addr_count;

	/* Clear RAR[1-15] */
	pr_debug("Clearing RAR[1-15]\n");
	for (i = rar_used_count; i < IXGB_RAR_ENTRIES; i++) {
		IXGB_WRITE_REG_ARRAY(hw, RA, (i << 1), 0);
		IXGB_WRITE_REG_ARRAY(hw, RA, ((i << 1) + 1), 0);
	}

	/* Clear the MTA */
	pr_debug("Clearing MTA\n");
	for (i = 0; i < IXGB_MC_TBL_SIZE; i++)
		IXGB_WRITE_REG_ARRAY(hw, MTA, i, 0);

	/* Add the new addresses */
	mca = mc_addr_list;
	for (i = 0; i < mc_addr_count; i++) {
		pr_debug("Adding the multicast addresses:\n");
		pr_debug("MC Addr #%d = %pM\n", i, mca);

		/* Place this multicast address in the RAR if there is room, *
		 * else put it in the MTA
		 */
		if (rar_used_count < IXGB_RAR_ENTRIES) {
			ixgb_rar_set(hw, mca, rar_used_count);
			pr_debug("Added a multicast address to RAR[%d]\n", i);
			rar_used_count++;
		} else {
			hash_value = ixgb_hash_mc_addr(hw, mca);

			pr_debug("Hash value = 0x%03X\n", hash_value);

			ixgb_mta_set(hw, hash_value);
		}

		mca += ETH_ALEN + pad;
	}

	pr_debug("MC Update Complete\n");
}