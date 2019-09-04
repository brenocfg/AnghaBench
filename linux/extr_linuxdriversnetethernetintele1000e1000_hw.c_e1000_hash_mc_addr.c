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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct e1000_hw {int mc_filter_type; } ;

/* Variables and functions */

u32 e1000_hash_mc_addr(struct e1000_hw *hw, u8 *mc_addr)
{
	u32 hash_value = 0;

	/* The portion of the address that is used for the hash table is
	 * determined by the mc_filter_type setting.
	 */
	switch (hw->mc_filter_type) {
		/* [0] [1] [2] [3] [4] [5]
		 * 01  AA  00  12  34  56
		 * LSB                 MSB
		 */
	case 0:
		/* [47:36] i.e. 0x563 for above example address */
		hash_value = ((mc_addr[4] >> 4) | (((u16)mc_addr[5]) << 4));
		break;
	case 1:
		/* [46:35] i.e. 0xAC6 for above example address */
		hash_value = ((mc_addr[4] >> 3) | (((u16)mc_addr[5]) << 5));
		break;
	case 2:
		/* [45:34] i.e. 0x5D8 for above example address */
		hash_value = ((mc_addr[4] >> 2) | (((u16)mc_addr[5]) << 6));
		break;
	case 3:
		/* [43:32] i.e. 0x634 for above example address */
		hash_value = ((mc_addr[4]) | (((u16)mc_addr[5]) << 8));
		break;
	}

	hash_value &= 0xFFF;
	return hash_value;
}