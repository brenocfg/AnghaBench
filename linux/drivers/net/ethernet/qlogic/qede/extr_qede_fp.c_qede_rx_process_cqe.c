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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct eth_fast_path_rx_reg_cqe {int type; size_t placement_offset; size_t bd_num; int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  rss_hash; int /*<<< orphan*/  bitfields; TYPE_2__ pars_flags; int /*<<< orphan*/  len_on_first_bd; } ;
union eth_rx_cqe {struct eth_fast_path_rx_reg_cqe fast_path_regular; } ;
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct sw_rx_data {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct qede_rx_queue {size_t sw_rx_cons; size_t rx_headroom; int /*<<< orphan*/  rxq_id; int /*<<< orphan*/  rx_alloc_errors; int /*<<< orphan*/  rx_hw_errors; int /*<<< orphan*/  rx_ip_frags; struct sw_rx_data* sw_rx_ring; int /*<<< orphan*/  rx_comp_ring; int /*<<< orphan*/  xdp_prog; } ;
struct qede_fastpath {int /*<<< orphan*/  id; } ;
struct qede_dev {int /*<<< orphan*/  ndev; int /*<<< orphan*/  cdev; TYPE_1__* ops; } ;
struct eth_slow_path_rx_cqe {int dummy; } ;
struct bpf_prog {int dummy; } ;
typedef  enum eth_rx_cqe_type { ____Placeholder_eth_rx_cqe_type } eth_rx_cqe_type ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* eth_cqe_completion ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eth_slow_path_rx_cqe*) ;} ;

/* Variables and functions */
 int ETH_RX_CQE_TYPE_REGULAR ; 
 int ETH_RX_CQE_TYPE_SLOW_PATH ; 
 size_t NUM_RX_BDS_MAX ; 
 scalar_t__ QEDE_CSUM_ERROR ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ qed_chain_consume (int /*<<< orphan*/ *) ; 
 scalar_t__ qede_check_csum (size_t) ; 
 int /*<<< orphan*/  qede_get_rxhash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qede_pkt_is_ip_fragmented (struct eth_fast_path_rx_reg_cqe*,size_t) ; 
 int /*<<< orphan*/  qede_ptp_record_rx_ts (struct qede_dev*,union eth_rx_cqe*,struct sk_buff*) ; 
 int /*<<< orphan*/  qede_recycle_rx_bd_ring (struct qede_rx_queue*,size_t) ; 
 size_t qede_rx_build_jumbo (struct qede_dev*,struct qede_rx_queue*,struct sk_buff*,struct eth_fast_path_rx_reg_cqe*,size_t) ; 
 struct sk_buff* qede_rx_build_skb (struct qede_dev*,struct qede_rx_queue*,struct sw_rx_data*,size_t,size_t) ; 
 int qede_rx_process_tpa_cqe (struct qede_dev*,struct qede_fastpath*,struct qede_rx_queue*,union eth_rx_cqe*,int) ; 
 int /*<<< orphan*/  qede_rx_xdp (struct qede_dev*,struct qede_fastpath*,struct qede_rx_queue*,struct bpf_prog*,struct sw_rx_data*,struct eth_fast_path_rx_reg_cqe*,size_t*,size_t*) ; 
 int /*<<< orphan*/  qede_set_skb_csum (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  qede_skb_receive (struct qede_dev*,struct qede_fastpath*,struct qede_rx_queue*,struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eth_slow_path_rx_cqe*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qede_rx_process_cqe(struct qede_dev *edev,
			       struct qede_fastpath *fp,
			       struct qede_rx_queue *rxq)
{
	struct bpf_prog *xdp_prog = READ_ONCE(rxq->xdp_prog);
	struct eth_fast_path_rx_reg_cqe *fp_cqe;
	u16 len, pad, bd_cons_idx, parse_flag;
	enum eth_rx_cqe_type cqe_type;
	union eth_rx_cqe *cqe;
	struct sw_rx_data *bd;
	struct sk_buff *skb;
	__le16 flags;
	u8 csum_flag;

	/* Get the CQE from the completion ring */
	cqe = (union eth_rx_cqe *)qed_chain_consume(&rxq->rx_comp_ring);
	cqe_type = cqe->fast_path_regular.type;

	/* Process an unlikely slowpath event */
	if (unlikely(cqe_type == ETH_RX_CQE_TYPE_SLOW_PATH)) {
		struct eth_slow_path_rx_cqe *sp_cqe;

		sp_cqe = (struct eth_slow_path_rx_cqe *)cqe;
		edev->ops->eth_cqe_completion(edev->cdev, fp->id, sp_cqe);
		return 0;
	}

	/* Handle TPA cqes */
	if (cqe_type != ETH_RX_CQE_TYPE_REGULAR)
		return qede_rx_process_tpa_cqe(edev, fp, rxq, cqe, cqe_type);

	/* Get the data from the SW ring; Consume it only after it's evident
	 * we wouldn't recycle it.
	 */
	bd_cons_idx = rxq->sw_rx_cons & NUM_RX_BDS_MAX;
	bd = &rxq->sw_rx_ring[bd_cons_idx];

	fp_cqe = &cqe->fast_path_regular;
	len = le16_to_cpu(fp_cqe->len_on_first_bd);
	pad = fp_cqe->placement_offset + rxq->rx_headroom;

	/* Run eBPF program if one is attached */
	if (xdp_prog)
		if (!qede_rx_xdp(edev, fp, rxq, xdp_prog, bd, fp_cqe,
				 &pad, &len))
			return 0;

	/* If this is an error packet then drop it */
	flags = cqe->fast_path_regular.pars_flags.flags;
	parse_flag = le16_to_cpu(flags);

	csum_flag = qede_check_csum(parse_flag);
	if (unlikely(csum_flag == QEDE_CSUM_ERROR)) {
		if (qede_pkt_is_ip_fragmented(fp_cqe, parse_flag))
			rxq->rx_ip_frags++;
		else
			rxq->rx_hw_errors++;
	}

	/* Basic validation passed; Need to prepare an SKB. This would also
	 * guarantee to finally consume the first BD upon success.
	 */
	skb = qede_rx_build_skb(edev, rxq, bd, len, pad);
	if (!skb) {
		rxq->rx_alloc_errors++;
		qede_recycle_rx_bd_ring(rxq, fp_cqe->bd_num);
		return 0;
	}

	/* In case of Jumbo packet, several PAGE_SIZEd buffers will be pointed
	 * by a single cqe.
	 */
	if (fp_cqe->bd_num > 1) {
		u16 unmapped_frags = qede_rx_build_jumbo(edev, rxq, skb,
							 fp_cqe, len);

		if (unlikely(unmapped_frags > 0)) {
			qede_recycle_rx_bd_ring(rxq, unmapped_frags);
			dev_kfree_skb_any(skb);
			return 0;
		}
	}

	/* The SKB contains all the data. Now prepare meta-magic */
	skb->protocol = eth_type_trans(skb, edev->ndev);
	qede_get_rxhash(skb, fp_cqe->bitfields, fp_cqe->rss_hash);
	qede_set_skb_csum(skb, csum_flag);
	skb_record_rx_queue(skb, rxq->rxq_id);
	qede_ptp_record_rx_ts(edev, cqe, skb);

	/* SKB is prepared - pass it to stack */
	qede_skb_receive(edev, fp, rxq, skb, le16_to_cpu(fp_cqe->vlan_tag));

	return 1;
}