#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct nfp_prog {unsigned int stack_size; unsigned int prog_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; TYPE_3__* netdev; } ;
struct nfp_net {TYPE_4__ dp; int /*<<< orphan*/  app_priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct bpf_prog {TYPE_2__* aux; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_pkt_offset; TYPE_1__* offload; } ;
struct TYPE_5__ {struct nfp_prog* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_ADDR ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_INL_MTU ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_MAX_LEN ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_SIZE ; 
 int /*<<< orphan*/  NFP_NET_CFG_BPF_STACK_SZ ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_BPF ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nfp_bpf_relo_for_vnic (struct nfp_prog*,int /*<<< orphan*/ ) ; 
 int nfp_net_reconfig (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int nn_readb (struct nfp_net*,int /*<<< orphan*/ ) ; 
 unsigned int nn_readw (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writeq (struct nfp_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_writew (struct nfp_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nfp_net_bpf_load(struct nfp_net *nn, struct bpf_prog *prog,
		 struct netlink_ext_ack *extack)
{
	struct nfp_prog *nfp_prog = prog->aux->offload->dev_priv;
	unsigned int fw_mtu, pkt_off, max_stack, max_prog_len;
	dma_addr_t dma_addr;
	void *img;
	int err;

	fw_mtu = nn_readb(nn, NFP_NET_CFG_BPF_INL_MTU) * 64 - 32;
	pkt_off = min(prog->aux->max_pkt_offset, nn->dp.netdev->mtu);
	if (fw_mtu < pkt_off) {
		NL_SET_ERR_MSG_MOD(extack, "BPF offload not supported with potential packet access beyond HW packet split boundary");
		return -EOPNOTSUPP;
	}

	max_stack = nn_readb(nn, NFP_NET_CFG_BPF_STACK_SZ) * 64;
	if (nfp_prog->stack_size > max_stack) {
		NL_SET_ERR_MSG_MOD(extack, "stack too large");
		return -EOPNOTSUPP;
	}

	max_prog_len = nn_readw(nn, NFP_NET_CFG_BPF_MAX_LEN);
	if (nfp_prog->prog_len > max_prog_len) {
		NL_SET_ERR_MSG_MOD(extack, "program too long");
		return -EOPNOTSUPP;
	}

	img = nfp_bpf_relo_for_vnic(nfp_prog, nn->app_priv);
	if (IS_ERR(img))
		return PTR_ERR(img);

	dma_addr = dma_map_single(nn->dp.dev, img,
				  nfp_prog->prog_len * sizeof(u64),
				  DMA_TO_DEVICE);
	if (dma_mapping_error(nn->dp.dev, dma_addr)) {
		kfree(img);
		return -ENOMEM;
	}

	nn_writew(nn, NFP_NET_CFG_BPF_SIZE, nfp_prog->prog_len);
	nn_writeq(nn, NFP_NET_CFG_BPF_ADDR, dma_addr);

	/* Load up the JITed code */
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_BPF);
	if (err)
		NL_SET_ERR_MSG_MOD(extack,
				   "FW command error while loading BPF");

	dma_unmap_single(nn->dp.dev, dma_addr, nfp_prog->prog_len * sizeof(u64),
			 DMA_TO_DEVICE);
	kfree(img);

	return err;
}