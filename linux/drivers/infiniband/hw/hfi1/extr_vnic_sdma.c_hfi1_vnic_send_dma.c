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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct vnic_txreq {size_t plen; int /*<<< orphan*/  txreq; int /*<<< orphan*/  pad; struct sk_buff* skb; struct hfi1_vnic_sdma* sdma; } ;
struct sk_buff {int dummy; } ;
struct sdma_engine {int dummy; } ;
struct hfi1_vnic_vport_info {struct hfi1_vnic_sdma* sdma; } ;
struct hfi1_vnic_sdma {int pkts_sent; int /*<<< orphan*/  wait; int /*<<< orphan*/  state; struct sdma_engine* sde; } ;
struct TYPE_2__ {int /*<<< orphan*/  txreq_cache; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;

/* Variables and functions */
 int EBUSY ; 
 int ECOMM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HFI1_VNIC_SDMA_Q_ACTIVE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int build_vnic_tx_desc (struct sdma_engine*,struct vnic_txreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  hfi1_vnic_update_pad (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  iowait_get_ib_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowait_starve_clear (int,int /*<<< orphan*/ *) ; 
 struct vnic_txreq* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vnic_txreq*) ; 
 int /*<<< orphan*/  sdma_running (struct sdma_engine*) ; 
 int sdma_send_txreq (struct sdma_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdma_txclean (struct hfi1_devdata*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int hfi1_vnic_send_dma(struct hfi1_devdata *dd, u8 q_idx,
		       struct hfi1_vnic_vport_info *vinfo,
		       struct sk_buff *skb, u64 pbc, u8 plen)
{
	struct hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[q_idx];
	struct sdma_engine *sde = vnic_sdma->sde;
	struct vnic_txreq *tx;
	int ret = -ECOMM;

	if (unlikely(READ_ONCE(vnic_sdma->state) != HFI1_VNIC_SDMA_Q_ACTIVE))
		goto tx_err;

	if (unlikely(!sde || !sdma_running(sde)))
		goto tx_err;

	tx = kmem_cache_alloc(dd->vnic.txreq_cache, GFP_ATOMIC);
	if (unlikely(!tx)) {
		ret = -ENOMEM;
		goto tx_err;
	}

	tx->sdma = vnic_sdma;
	tx->skb = skb;
	hfi1_vnic_update_pad(tx->pad, plen);
	tx->plen = plen;
	ret = build_vnic_tx_desc(sde, tx, pbc);
	if (unlikely(ret))
		goto free_desc;

	ret = sdma_send_txreq(sde, iowait_get_ib_work(&vnic_sdma->wait),
			      &tx->txreq, vnic_sdma->pkts_sent);
	/* When -ECOMM, sdma callback will be called with ABORT status */
	if (unlikely(ret && unlikely(ret != -ECOMM)))
		goto free_desc;

	if (!ret) {
		vnic_sdma->pkts_sent = true;
		iowait_starve_clear(vnic_sdma->pkts_sent, &vnic_sdma->wait);
	}
	return ret;

free_desc:
	sdma_txclean(dd, &tx->txreq);
	kmem_cache_free(dd->vnic.txreq_cache, tx);
tx_err:
	if (ret != -EBUSY)
		dev_kfree_skb_any(skb);
	else
		vnic_sdma->pkts_sent = false;
	return ret;
}