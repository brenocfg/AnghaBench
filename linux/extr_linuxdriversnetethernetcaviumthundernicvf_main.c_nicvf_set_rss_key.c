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
struct nicvf_rss_info {int /*<<< orphan*/ * key; } ;
struct nicvf {struct nicvf_rss_info rss_info; } ;

/* Variables and functions */
 int NIC_VNIC_RSS_KEY_0_4 ; 
 int RSS_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  nicvf_reg_write (struct nicvf*,int,int /*<<< orphan*/ ) ; 

void nicvf_set_rss_key(struct nicvf *nic)
{
	struct nicvf_rss_info *rss = &nic->rss_info;
	u64 key_addr = NIC_VNIC_RSS_KEY_0_4;
	int idx;

	for (idx = 0; idx < RSS_HASH_KEY_SIZE; idx++) {
		nicvf_reg_write(nic, key_addr, rss->key[idx]);
		key_addr += sizeof(u64);
	}
}