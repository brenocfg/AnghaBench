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
typedef  unsigned char u32 ;
struct pxa168_eth_private {int /*<<< orphan*/  dev; struct addr_table_entry* htpr; } ;
struct addr_table_entry {void* lo; void* hi; } ;

/* Variables and functions */
 int ENOSPC ; 
 unsigned char HASH_ENTRY_RECEIVE_DISCARD_BIT ; 
 unsigned char HASH_ENTRY_VALID ; 
 unsigned char HOP_NUMBER ; 
 unsigned char SKIP ; 
 void* cpu_to_le32 (unsigned char) ; 
 int hash_function (unsigned char*) ; 
 unsigned char le32_to_cpu (void*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int add_del_hash_entry(struct pxa168_eth_private *pep,
			      unsigned char *mac_addr,
			      u32 rd, u32 skip, int del)
{
	struct addr_table_entry *entry, *start;
	u32 new_high;
	u32 new_low;
	u32 i;

	new_low = (((mac_addr[1] >> 4) & 0xf) << 15)
	    | (((mac_addr[1] >> 0) & 0xf) << 11)
	    | (((mac_addr[0] >> 4) & 0xf) << 7)
	    | (((mac_addr[0] >> 0) & 0xf) << 3)
	    | (((mac_addr[3] >> 4) & 0x1) << 31)
	    | (((mac_addr[3] >> 0) & 0xf) << 27)
	    | (((mac_addr[2] >> 4) & 0xf) << 23)
	    | (((mac_addr[2] >> 0) & 0xf) << 19)
	    | (skip << SKIP) | (rd << HASH_ENTRY_RECEIVE_DISCARD_BIT)
	    | HASH_ENTRY_VALID;

	new_high = (((mac_addr[5] >> 4) & 0xf) << 15)
	    | (((mac_addr[5] >> 0) & 0xf) << 11)
	    | (((mac_addr[4] >> 4) & 0xf) << 7)
	    | (((mac_addr[4] >> 0) & 0xf) << 3)
	    | (((mac_addr[3] >> 5) & 0x7) << 0);

	/*
	 * Pick the appropriate table, start scanning for free/reusable
	 * entries at the index obtained by hashing the specified MAC address
	 */
	start = pep->htpr;
	entry = start + hash_function(mac_addr);
	for (i = 0; i < HOP_NUMBER; i++) {
		if (!(le32_to_cpu(entry->lo) & HASH_ENTRY_VALID)) {
			break;
		} else {
			/* if same address put in same position */
			if (((le32_to_cpu(entry->lo) & 0xfffffff8) ==
				(new_low & 0xfffffff8)) &&
				(le32_to_cpu(entry->hi) == new_high)) {
				break;
			}
		}
		if (entry == start + 0x7ff)
			entry = start;
		else
			entry++;
	}

	if (((le32_to_cpu(entry->lo) & 0xfffffff8) != (new_low & 0xfffffff8)) &&
	    (le32_to_cpu(entry->hi) != new_high) && del)
		return 0;

	if (i == HOP_NUMBER) {
		if (!del) {
			netdev_info(pep->dev,
				    "%s: table section is full, need to "
				    "move to 16kB implementation?\n",
				    __FILE__);
			return -ENOSPC;
		} else
			return 0;
	}

	/*
	 * Update the selected entry
	 */
	if (del) {
		entry->hi = 0;
		entry->lo = 0;
	} else {
		entry->hi = cpu_to_le32(new_high);
		entry->lo = cpu_to_le32(new_low);
	}

	return 0;
}