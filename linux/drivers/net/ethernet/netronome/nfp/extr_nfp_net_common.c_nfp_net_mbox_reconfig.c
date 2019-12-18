#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ mbox_off; } ;
struct nfp_net {TYPE_1__ tlv_caps; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_CFG_MBOX_SIMPLE_CMD ; 
 scalar_t__ NFP_NET_CFG_MBOX_SIMPLE_RET ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_MBOX ; 
 int __nfp_net_reconfig (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_err (struct nfp_net*,char*) ; 
 int nn_readl (struct nfp_net*,scalar_t__) ; 
 int /*<<< orphan*/  nn_writeq (struct nfp_net*,scalar_t__,scalar_t__) ; 

int nfp_net_mbox_reconfig(struct nfp_net *nn, u32 mbox_cmd)
{
	u32 mbox = nn->tlv_caps.mbox_off;
	int ret;

	nn_writeq(nn, mbox + NFP_NET_CFG_MBOX_SIMPLE_CMD, mbox_cmd);

	ret = __nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_MBOX);
	if (ret) {
		nn_err(nn, "Mailbox update error\n");
		return ret;
	}

	return -nn_readl(nn, mbox + NFP_NET_CFG_MBOX_SIMPLE_RET);
}