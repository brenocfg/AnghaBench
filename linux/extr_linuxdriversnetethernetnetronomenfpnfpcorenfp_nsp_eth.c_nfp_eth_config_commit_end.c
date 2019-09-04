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
typedef  union eth_table_entry {int dummy; } eth_table_entry ;
struct nfp_nsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSP_ETH_TABLE_SIZE ; 
 int /*<<< orphan*/  nfp_eth_config_cleanup_end (struct nfp_nsp*) ; 
 union eth_table_entry* nfp_nsp_config_entries (struct nfp_nsp*) ; 
 scalar_t__ nfp_nsp_config_modified (struct nfp_nsp*) ; 
 int nfp_nsp_write_eth_table (struct nfp_nsp*,union eth_table_entry*,int /*<<< orphan*/ ) ; 

int nfp_eth_config_commit_end(struct nfp_nsp *nsp)
{
	union eth_table_entry *entries = nfp_nsp_config_entries(nsp);
	int ret = 1;

	if (nfp_nsp_config_modified(nsp)) {
		ret = nfp_nsp_write_eth_table(nsp, entries, NSP_ETH_TABLE_SIZE);
		ret = ret < 0 ? ret : 0;
	}

	nfp_eth_config_cleanup_end(nsp);

	return ret;
}