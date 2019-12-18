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
typedef  int u32 ;
struct nfp_net {int /*<<< orphan*/  reconfig_in_progress_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_CTRL ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE ; 
 int NFP_NET_CFG_UPDATE_ERR ; 
 int /*<<< orphan*/  nn_err (struct nfp_net*,char*,int,int /*<<< orphan*/ ,int) ; 
 int nn_readl (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfp_net_reconfig_check_done(struct nfp_net *nn, bool last_check)
{
	u32 reg;

	reg = nn_readl(nn, NFP_NET_CFG_UPDATE);
	if (reg == 0)
		return true;
	if (reg & NFP_NET_CFG_UPDATE_ERR) {
		nn_err(nn, "Reconfig error (status: 0x%08x update: 0x%08x ctrl: 0x%08x)\n",
		       reg, nn->reconfig_in_progress_update,
		       nn_readl(nn, NFP_NET_CFG_CTRL));
		return true;
	} else if (last_check) {
		nn_err(nn, "Reconfig timeout (status: 0x%08x update: 0x%08x ctrl: 0x%08x)\n",
		       reg, nn->reconfig_in_progress_update,
		       nn_readl(nn, NFP_NET_CFG_CTRL));
		return true;
	}

	return false;
}