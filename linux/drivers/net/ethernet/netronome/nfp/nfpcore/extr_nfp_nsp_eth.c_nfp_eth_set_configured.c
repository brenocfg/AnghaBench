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
union eth_table_entry {int /*<<< orphan*/  control; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nfp_nsp {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_ERR (struct nfp_nsp*) ; 
 int /*<<< orphan*/  NSP_ETH_CTRL_CONFIGURED ; 
 int /*<<< orphan*/  NSP_ETH_STATE_CONFIGURED ; 
 int PTR_ERR (struct nfp_nsp*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_eth_config_cleanup_end (struct nfp_nsp*) ; 
 int nfp_eth_config_commit_end (struct nfp_nsp*) ; 
 struct nfp_nsp* nfp_eth_config_start (struct nfp_cpp*,unsigned int) ; 
 union eth_table_entry* nfp_nsp_config_entries (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_config_set_modified (struct nfp_nsp*,int) ; 
 int nfp_nsp_get_abi_ver_minor (struct nfp_nsp*) ; 

int nfp_eth_set_configured(struct nfp_cpp *cpp, unsigned int idx, bool configed)
{
	union eth_table_entry *entries;
	struct nfp_nsp *nsp;
	u64 reg;

	nsp = nfp_eth_config_start(cpp, idx);
	if (IS_ERR(nsp))
		return PTR_ERR(nsp);

	/* Older ABI versions did support this feature, however this has only
	 * been reliable since ABI 20.
	 */
	if (nfp_nsp_get_abi_ver_minor(nsp) < 20) {
		nfp_eth_config_cleanup_end(nsp);
		return -EOPNOTSUPP;
	}

	entries = nfp_nsp_config_entries(nsp);

	/* Check if we are already in requested state */
	reg = le64_to_cpu(entries[idx].state);
	if (configed != FIELD_GET(NSP_ETH_STATE_CONFIGURED, reg)) {
		reg = le64_to_cpu(entries[idx].control);
		reg &= ~NSP_ETH_CTRL_CONFIGURED;
		reg |= FIELD_PREP(NSP_ETH_CTRL_CONFIGURED, configed);
		entries[idx].control = cpu_to_le64(reg);

		nfp_nsp_config_set_modified(nsp, true);
	}

	return nfp_eth_config_commit_end(nsp);
}