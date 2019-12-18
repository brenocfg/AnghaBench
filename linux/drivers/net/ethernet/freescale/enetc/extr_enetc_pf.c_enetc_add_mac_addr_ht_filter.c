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
struct enetc_mac_filter {int /*<<< orphan*/  mac_addr_cnt; int /*<<< orphan*/  mac_hash_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int enetc_mac_addr_hash_idx (unsigned char const*) ; 

__attribute__((used)) static void enetc_add_mac_addr_ht_filter(struct enetc_mac_filter *filter,
					 const unsigned char *addr)
{
	int idx = enetc_mac_addr_hash_idx(addr);

	/* add hash table entry */
	__set_bit(idx, filter->mac_hash_table);
	filter->mac_addr_cnt++;
}