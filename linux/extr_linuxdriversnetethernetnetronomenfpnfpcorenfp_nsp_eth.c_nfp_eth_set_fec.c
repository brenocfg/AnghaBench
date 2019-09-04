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
struct nfp_nsp {int dummy; } ;
struct nfp_cpp {int dummy; } ;
typedef  enum nfp_eth_fec { ____Placeholder_nfp_eth_fec } nfp_eth_fec ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfp_nsp*) ; 
 int PTR_ERR (struct nfp_nsp*) ; 
 int __nfp_eth_set_fec (struct nfp_nsp*,int) ; 
 int /*<<< orphan*/  nfp_eth_config_cleanup_end (struct nfp_nsp*) ; 
 int nfp_eth_config_commit_end (struct nfp_nsp*) ; 
 struct nfp_nsp* nfp_eth_config_start (struct nfp_cpp*,unsigned int) ; 

int
nfp_eth_set_fec(struct nfp_cpp *cpp, unsigned int idx, enum nfp_eth_fec mode)
{
	struct nfp_nsp *nsp;
	int err;

	nsp = nfp_eth_config_start(cpp, idx);
	if (IS_ERR(nsp))
		return PTR_ERR(nsp);

	err = __nfp_eth_set_fec(nsp, mode);
	if (err) {
		nfp_eth_config_cleanup_end(nsp);
		return err;
	}

	return nfp_eth_config_commit_end(nsp);
}