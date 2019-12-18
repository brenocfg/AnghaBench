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
typedef  scalar_t__ u16 ;
struct xdp_umem_fq_reuse {int dummy; } ;
struct xdp_umem {int dummy; } ;
struct net_device {scalar_t__ real_num_rx_queues; scalar_t__ real_num_tx_queues; } ;
struct i40e_vsi {scalar_t__ type; scalar_t__ num_queue_pairs; struct net_device* netdev; int /*<<< orphan*/  af_xdp_zc_qps; TYPE_1__** rx_rings; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  XDP_WAKEUP_RX ; 
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int i40e_queue_pair_disable (struct i40e_vsi*,scalar_t__) ; 
 int i40e_queue_pair_enable (struct i40e_vsi*,scalar_t__) ; 
 int i40e_xsk_umem_dma_map (struct i40e_vsi*,struct xdp_umem*) ; 
 int i40e_xsk_wakeup (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_reuseq_free (int /*<<< orphan*/ ) ; 
 struct xdp_umem_fq_reuse* xsk_reuseq_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_reuseq_swap (struct xdp_umem*,struct xdp_umem_fq_reuse*) ; 

__attribute__((used)) static int i40e_xsk_umem_enable(struct i40e_vsi *vsi, struct xdp_umem *umem,
				u16 qid)
{
	struct net_device *netdev = vsi->netdev;
	struct xdp_umem_fq_reuse *reuseq;
	bool if_running;
	int err;

	if (vsi->type != I40E_VSI_MAIN)
		return -EINVAL;

	if (qid >= vsi->num_queue_pairs)
		return -EINVAL;

	if (qid >= netdev->real_num_rx_queues ||
	    qid >= netdev->real_num_tx_queues)
		return -EINVAL;

	reuseq = xsk_reuseq_prepare(vsi->rx_rings[0]->count);
	if (!reuseq)
		return -ENOMEM;

	xsk_reuseq_free(xsk_reuseq_swap(umem, reuseq));

	err = i40e_xsk_umem_dma_map(vsi, umem);
	if (err)
		return err;

	set_bit(qid, vsi->af_xdp_zc_qps);

	if_running = netif_running(vsi->netdev) && i40e_enabled_xdp_vsi(vsi);

	if (if_running) {
		err = i40e_queue_pair_disable(vsi, qid);
		if (err)
			return err;

		err = i40e_queue_pair_enable(vsi, qid);
		if (err)
			return err;

		/* Kick start the NAPI context so that receiving will start */
		err = i40e_xsk_wakeup(vsi->netdev, qid, XDP_WAKEUP_RX);
		if (err)
			return err;
	}

	return 0;
}