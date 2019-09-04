#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct mlx4_ib_qp {TYPE_2__* sqp_proxy_rcv; TYPE_1__ ibqp; } ;
struct TYPE_6__ {int g_ml_path; int /*<<< orphan*/  sl_vid; int /*<<< orphan*/  slid_mac_47_32; int /*<<< orphan*/  mac_31_0; int /*<<< orphan*/  flags_src_qp; int /*<<< orphan*/  pkey_index; } ;
struct mlx4_ib_proxy_sqp_hdr {TYPE_3__ tun; } ;
struct mlx4_ib_cq {int dummy; } ;
struct mlx4_cqe {int dummy; } ;
struct ib_wc {int pkey_index; int src_qp; int wc_flags; int slid; int vlan_id; scalar_t__ sl; int /*<<< orphan*/ * smac; scalar_t__ dlid_path_bits; } ;
struct TYPE_5__ {scalar_t__ addr; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int IB_WC_GRH ; 
 int IB_WC_WITH_SMAC ; 
 int IB_WC_WITH_VLAN ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void use_tunnel_data(struct mlx4_ib_qp *qp, struct mlx4_ib_cq *cq, struct ib_wc *wc,
			    unsigned tail, struct mlx4_cqe *cqe, int is_eth)
{
	struct mlx4_ib_proxy_sqp_hdr *hdr;

	ib_dma_sync_single_for_cpu(qp->ibqp.device,
				   qp->sqp_proxy_rcv[tail].map,
				   sizeof (struct mlx4_ib_proxy_sqp_hdr),
				   DMA_FROM_DEVICE);
	hdr = (struct mlx4_ib_proxy_sqp_hdr *) (qp->sqp_proxy_rcv[tail].addr);
	wc->pkey_index	= be16_to_cpu(hdr->tun.pkey_index);
	wc->src_qp	= be32_to_cpu(hdr->tun.flags_src_qp) & 0xFFFFFF;
	wc->wc_flags   |= (hdr->tun.g_ml_path & 0x80) ? (IB_WC_GRH) : 0;
	wc->dlid_path_bits = 0;

	if (is_eth) {
		wc->slid = 0;
		wc->vlan_id = be16_to_cpu(hdr->tun.sl_vid);
		memcpy(&(wc->smac[0]), (char *)&hdr->tun.mac_31_0, 4);
		memcpy(&(wc->smac[4]), (char *)&hdr->tun.slid_mac_47_32, 2);
		wc->wc_flags |= (IB_WC_WITH_VLAN | IB_WC_WITH_SMAC);
	} else {
		wc->slid        = be16_to_cpu(hdr->tun.slid_mac_47_32);
		wc->sl          = (u8) (be16_to_cpu(hdr->tun.sl_vid) >> 12);
	}
}