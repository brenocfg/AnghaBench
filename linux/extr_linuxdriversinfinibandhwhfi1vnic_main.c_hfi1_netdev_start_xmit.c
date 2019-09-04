#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct sk_buff {size_t queue_mapping; int len; scalar_t__ data; } ;
struct opa_vnic_skb_mdata {int flags; int /*<<< orphan*/  vl; } ;
struct net_device {int dummy; } ;
struct hfi1_vnic_vport_info {TYPE_2__* stats; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int (* process_vnic_dma_send ) (struct hfi1_devdata*,size_t,struct hfi1_vnic_vport_info*,struct sk_buff*,int /*<<< orphan*/ ,size_t) ;} ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_3__ {int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_fifo_errors; } ;
struct TYPE_4__ {TYPE_1__ netstats; int /*<<< orphan*/  tx_dlid_zero; int /*<<< orphan*/  tx_drop_state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int OPA_VNIC_HDR_LEN ; 
 int OPA_VNIC_ICRC_TAIL_LEN ; 
 int OPA_VNIC_SKB_MDATA_ENCAP_ERR ; 
 int /*<<< orphan*/  create_bypass_pbc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  hfi1_vnic_maybe_stop_tx (struct hfi1_vnic_vport_info*,size_t) ; 
 int /*<<< orphan*/  hfi1_vnic_update_tx_counters (struct hfi1_vnic_vport_info*,size_t,struct sk_buff*,int) ; 
 int /*<<< orphan*/  netif_oper_up (struct net_device*) ; 
 struct hfi1_vnic_vport_info* opa_vnic_dev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int stub1 (struct hfi1_devdata*,size_t,struct hfi1_vnic_vport_info*,struct sk_buff*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  v_dbg (char*,size_t,size_t,...) ; 

__attribute__((used)) static netdev_tx_t hfi1_netdev_start_xmit(struct sk_buff *skb,
					  struct net_device *netdev)
{
	struct hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);
	u8 pad_len, q_idx = skb->queue_mapping;
	struct hfi1_devdata *dd = vinfo->dd;
	struct opa_vnic_skb_mdata *mdata;
	u32 pkt_len, total_len;
	int err = -EINVAL;
	u64 pbc;

	v_dbg("xmit: queue %d skb len %d\n", q_idx, skb->len);
	if (unlikely(!netif_oper_up(netdev))) {
		vinfo->stats[q_idx].tx_drop_state++;
		goto tx_finish;
	}

	/* take out meta data */
	mdata = (struct opa_vnic_skb_mdata *)skb->data;
	skb_pull(skb, sizeof(*mdata));
	if (unlikely(mdata->flags & OPA_VNIC_SKB_MDATA_ENCAP_ERR)) {
		vinfo->stats[q_idx].tx_dlid_zero++;
		goto tx_finish;
	}

	/* add tail padding (for 8 bytes size alignment) and icrc */
	pad_len = -(skb->len + OPA_VNIC_ICRC_TAIL_LEN) & 0x7;
	pad_len += OPA_VNIC_ICRC_TAIL_LEN;

	/*
	 * pkt_len is how much data we have to write, includes header and data.
	 * total_len is length of the packet in Dwords plus the PBC should not
	 * include the CRC.
	 */
	pkt_len = (skb->len + pad_len) >> 2;
	total_len = pkt_len + 2; /* PBC + packet */

	pbc = create_bypass_pbc(mdata->vl, total_len);

	skb_get(skb);
	v_dbg("pbc 0x%016llX len %d pad_len %d\n", pbc, skb->len, pad_len);
	err = dd->process_vnic_dma_send(dd, q_idx, vinfo, skb, pbc, pad_len);
	if (unlikely(err)) {
		if (err == -ENOMEM)
			vinfo->stats[q_idx].netstats.tx_fifo_errors++;
		else if (err != -EBUSY)
			vinfo->stats[q_idx].netstats.tx_carrier_errors++;
	}
	/* remove the header before updating tx counters */
	skb_pull(skb, OPA_VNIC_HDR_LEN);

	if (unlikely(err == -EBUSY)) {
		hfi1_vnic_maybe_stop_tx(vinfo, q_idx);
		dev_kfree_skb_any(skb);
		return NETDEV_TX_BUSY;
	}

tx_finish:
	/* update tx counters */
	hfi1_vnic_update_tx_counters(vinfo, q_idx, skb, err);
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}