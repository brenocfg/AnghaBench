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
 int /*<<< orphan*/  kfree (union eth_table_entry*) ; 
 int /*<<< orphan*/  nfp_nsp_close (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_config_clear_state (struct nfp_nsp*) ; 
 union eth_table_entry* nfp_nsp_config_entries (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_config_set_modified (struct nfp_nsp*,int) ; 

void nfp_eth_config_cleanup_end(struct nfp_nsp *nsp)
{
	union eth_table_entry *entries = nfp_nsp_config_entries(nsp);

	nfp_nsp_config_set_modified(nsp, false);
	nfp_nsp_config_clear_state(nsp);
	nfp_nsp_close(nsp);
	kfree(entries);
}