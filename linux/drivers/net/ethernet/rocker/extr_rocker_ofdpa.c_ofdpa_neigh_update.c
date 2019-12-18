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
struct ofdpa_neigh_tbl_entry {int ttl_check; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  eth_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void ofdpa_neigh_update(struct ofdpa_neigh_tbl_entry *entry,
			       const u8 *eth_dst, bool ttl_check)
{
	if (eth_dst) {
		ether_addr_copy(entry->eth_dst, eth_dst);
		entry->ttl_check = ttl_check;
	} else {
		entry->ref_count++;
	}
}