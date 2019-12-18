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
typedef  size_t u8 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct hfi1_vnic_vport_info {TYPE_4__* stats; int /*<<< orphan*/  netdev; struct hfi1_vnic_rx_queue* rxq; } ;
struct hfi1_vnic_rx_queue {int /*<<< orphan*/  napi; int /*<<< orphan*/  skbq; } ;
struct hfi1_packet {int /*<<< orphan*/  tlen; int /*<<< orphan*/  ebuf; TYPE_2__* rcd; } ;
struct TYPE_5__ {int /*<<< orphan*/  vesws; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_nohandler; } ;
struct TYPE_8__ {TYPE_3__ netstats; int /*<<< orphan*/  rx_drop_state; } ;
struct TYPE_6__ {size_t vnic_q_idx; int /*<<< orphan*/  ctxt; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int HFI1_VNIC_GET_VESWID (int /*<<< orphan*/ ) ; 
 scalar_t__ HFI1_VNIC_RCV_Q_SIZE ; 
 int OPA_16B_L4_ETHR ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  XA_PRESENT ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dd_dev_warn (struct hfi1_devdata*,char*,int,int,int /*<<< orphan*/ ) ; 
 int hfi1_16B_get_l4 (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_oper_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  v_dbg (char*,size_t) ; 
 int /*<<< orphan*/  vport_cntr_lock ; 
 struct hfi1_vnic_vport_info* xa_find (int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hfi1_vnic_vport_info* xa_load (int /*<<< orphan*/ *,int) ; 

void hfi1_vnic_bypass_rcv(struct hfi1_packet *packet)
{
	struct hfi1_devdata *dd = packet->rcd->dd;
	struct hfi1_vnic_vport_info *vinfo = NULL;
	struct hfi1_vnic_rx_queue *rxq;
	struct sk_buff *skb;
	int l4_type, vesw_id = -1;
	u8 q_idx;

	l4_type = hfi1_16B_get_l4(packet->ebuf);
	if (likely(l4_type == OPA_16B_L4_ETHR)) {
		vesw_id = HFI1_VNIC_GET_VESWID(packet->ebuf);
		vinfo = xa_load(&dd->vnic.vesws, vesw_id);

		/*
		 * In case of invalid vesw id, count the error on
		 * the first available vport.
		 */
		if (unlikely(!vinfo)) {
			struct hfi1_vnic_vport_info *vinfo_tmp;
			unsigned long index = 0;

			vinfo_tmp = xa_find(&dd->vnic.vesws, &index, ULONG_MAX,
					XA_PRESENT);
			if (vinfo_tmp) {
				spin_lock(&vport_cntr_lock);
				vinfo_tmp->stats[0].netstats.rx_nohandler++;
				spin_unlock(&vport_cntr_lock);
			}
		}
	}

	if (unlikely(!vinfo)) {
		dd_dev_warn(dd, "vnic rcv err: l4 %d vesw id %d ctx %d\n",
			    l4_type, vesw_id, packet->rcd->ctxt);
		return;
	}

	q_idx = packet->rcd->vnic_q_idx;
	rxq = &vinfo->rxq[q_idx];
	if (unlikely(!netif_oper_up(vinfo->netdev))) {
		vinfo->stats[q_idx].rx_drop_state++;
		skb_queue_purge(&rxq->skbq);
		return;
	}

	if (unlikely(skb_queue_len(&rxq->skbq) > HFI1_VNIC_RCV_Q_SIZE)) {
		vinfo->stats[q_idx].netstats.rx_fifo_errors++;
		return;
	}

	skb = netdev_alloc_skb(vinfo->netdev, packet->tlen);
	if (unlikely(!skb)) {
		vinfo->stats[q_idx].netstats.rx_fifo_errors++;
		return;
	}

	memcpy(skb->data, packet->ebuf, packet->tlen);
	skb_put(skb, packet->tlen);
	skb_queue_tail(&rxq->skbq, skb);

	if (napi_schedule_prep(&rxq->napi)) {
		v_dbg("napi %d scheduling\n", q_idx);
		__napi_schedule(&rxq->napi);
	}
}