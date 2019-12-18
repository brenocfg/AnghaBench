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
struct nfp_pf {int /*<<< orphan*/  cpp; } ;
struct nfp_nsp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfp_nsp*) ; 
 int PTR_ERR (struct nfp_nsp*) ; 
 int __nfp_eth_set_split (struct nfp_nsp*,unsigned int) ; 
 int /*<<< orphan*/  nfp_eth_config_cleanup_end (struct nfp_nsp*) ; 
 int nfp_eth_config_commit_end (struct nfp_nsp*) ; 
 struct nfp_nsp* nfp_eth_config_start (int /*<<< orphan*/ ,unsigned int) ; 
 int nfp_net_refresh_port_table_sync (struct nfp_pf*) ; 

__attribute__((used)) static int
nfp_devlink_set_lanes(struct nfp_pf *pf, unsigned int idx, unsigned int lanes)
{
	struct nfp_nsp *nsp;
	int ret;

	nsp = nfp_eth_config_start(pf->cpp, idx);
	if (IS_ERR(nsp))
		return PTR_ERR(nsp);

	ret = __nfp_eth_set_split(nsp, lanes);
	if (ret) {
		nfp_eth_config_cleanup_end(nsp);
		return ret;
	}

	ret = nfp_eth_config_commit_end(nsp);
	if (ret < 0)
		return ret;
	if (ret) /* no change */
		return 0;

	return nfp_net_refresh_port_table_sync(pf);
}