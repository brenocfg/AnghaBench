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
typedef  int u8 ;
struct TYPE_2__ {int ctrl; int /*<<< orphan*/  netdev; } ;
struct nfp_net {TYPE_1__ dp; } ;
struct netlink_ext_ack {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int NFP_NET_BPF_CAP_RELO ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_CAP ; 
 int NFP_NET_CFG_CTRL_BPF ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  bpf_offload_dev_match (struct bpf_prog*,int /*<<< orphan*/ ) ; 
 int nfp_net_bpf_load (struct nfp_net*,struct bpf_prog*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nfp_net_bpf_start (struct nfp_net*,struct netlink_ext_ack*) ; 
 int nfp_net_bpf_stop (struct nfp_net*) ; 
 int nn_readb (struct nfp_net*,int /*<<< orphan*/ ) ; 

int nfp_net_bpf_offload(struct nfp_net *nn, struct bpf_prog *prog,
			bool old_prog, struct netlink_ext_ack *extack)
{
	int err;

	if (prog && !bpf_offload_dev_match(prog, nn->dp.netdev))
		return -EINVAL;

	if (prog && old_prog) {
		u8 cap;

		cap = nn_readb(nn, NFP_NET_CFG_BPF_CAP);
		if (!(cap & NFP_NET_BPF_CAP_RELO)) {
			NL_SET_ERR_MSG_MOD(extack,
					   "FW does not support live reload");
			return -EBUSY;
		}
	}

	/* Something else is loaded, different program type? */
	if (!old_prog && nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF)
		return -EBUSY;

	if (old_prog && !prog)
		return nfp_net_bpf_stop(nn);

	err = nfp_net_bpf_load(nn, prog, extack);
	if (err)
		return err;

	if (!old_prog)
		nfp_net_bpf_start(nn, extack);

	return 0;
}