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
struct nfp_net {int cap; TYPE_1__* app; } ;
struct nfp_app_bpf {scalar_t__ abi_version; } ;
struct TYPE_2__ {struct nfp_app_bpf* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_BPF_ABI ; 
 int NFP_NET_CFG_CTRL_BPF ; 
 scalar_t__ nn_readb (struct nfp_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfp_net_ebpf_capable(struct nfp_net *nn)
{
#ifdef __LITTLE_ENDIAN
	struct nfp_app_bpf *bpf = nn->app->priv;

	return nn->cap & NFP_NET_CFG_CTRL_BPF &&
	       bpf->abi_version &&
	       nn_readb(nn, NFP_NET_CFG_BPF_ABI) == bpf->abi_version;
#else
	return false;
#endif
}