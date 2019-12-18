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
union eth_table_entry {int port; } ;
struct nfp_nsp {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nfp_nsp* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct nfp_nsp*) ; 
 int NSP_ETH_PORT_LANES_MASK ; 
 int /*<<< orphan*/  NSP_ETH_TABLE_SIZE ; 
 int /*<<< orphan*/  kfree (union eth_table_entry*) ; 
 union eth_table_entry* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,int) ; 
 int /*<<< orphan*/  nfp_nsp_close (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_config_set_state (struct nfp_nsp*,union eth_table_entry*,unsigned int) ; 
 struct nfp_nsp* nfp_nsp_open (struct nfp_cpp*) ; 
 int nfp_nsp_read_eth_table (struct nfp_nsp*,union eth_table_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_warn (struct nfp_cpp*,char*,unsigned int) ; 

struct nfp_nsp *nfp_eth_config_start(struct nfp_cpp *cpp, unsigned int idx)
{
	union eth_table_entry *entries;
	struct nfp_nsp *nsp;
	int ret;

	entries = kzalloc(NSP_ETH_TABLE_SIZE, GFP_KERNEL);
	if (!entries)
		return ERR_PTR(-ENOMEM);

	nsp = nfp_nsp_open(cpp);
	if (IS_ERR(nsp)) {
		kfree(entries);
		return nsp;
	}

	ret = nfp_nsp_read_eth_table(nsp, entries, NSP_ETH_TABLE_SIZE);
	if (ret < 0) {
		nfp_err(cpp, "reading port table failed %d\n", ret);
		goto err;
	}

	if (!(entries[idx].port & NSP_ETH_PORT_LANES_MASK)) {
		nfp_warn(cpp, "trying to set port state on disabled port %d\n",
			 idx);
		goto err;
	}

	nfp_nsp_config_set_state(nsp, entries, idx);
	return nsp;

err:
	nfp_nsp_close(nsp);
	kfree(entries);
	return ERR_PTR(-EIO);
}