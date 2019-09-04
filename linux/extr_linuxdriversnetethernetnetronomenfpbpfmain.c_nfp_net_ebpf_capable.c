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
struct nfp_net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool nfp_net_ebpf_capable(struct nfp_net *nn)
{
#ifdef __LITTLE_ENDIAN
	if (nn->cap & NFP_NET_CFG_CTRL_BPF &&
	    nn_readb(nn, NFP_NET_CFG_BPF_ABI) == NFP_NET_BPF_ABI)
		return true;
#endif
	return false;
}