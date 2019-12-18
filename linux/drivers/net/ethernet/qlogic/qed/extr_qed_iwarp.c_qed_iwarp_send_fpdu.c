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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  tx_pkt ;
struct unaligned_opaque_data {scalar_t__ first_mpa_offset; } ;
struct qed_ll2_tx_pkt_info {int num_of_bds; int l4_hdr_offset_w; int first_frag_len; int enable_ip_cksum; int enable_l4_cksum; int calc_ip_len; int /*<<< orphan*/  vlan; int /*<<< orphan*/  first_frag; TYPE_1__* cookie; int /*<<< orphan*/  tx_dest; } ;
struct qed_iwarp_ll2_buff {scalar_t__ data_phys_addr; } ;
struct qed_iwarp_fpdu {int pkt_hdr_size; scalar_t__ fpdu_length; scalar_t__ incomplete_bytes; scalar_t__ mpa_frag_len; scalar_t__ mpa_frag; TYPE_1__* mpa_buf; int /*<<< orphan*/  pkt_hdr; } ;
struct qed_hwfn {TYPE_3__* p_rdma_info; } ;
typedef  enum qed_iwarp_mpa_pkt_type { ____Placeholder_qed_iwarp_mpa_pkt_type } qed_iwarp_mpa_pkt_type ;
struct TYPE_5__ {int /*<<< orphan*/  ll2_mpa_handle; } ;
struct TYPE_6__ {TYPE_2__ iwarp; } ;
struct TYPE_4__ {struct qed_iwarp_ll2_buff* piggy_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  IWARP_LL2_ALIGNED_TX_QUEUE ; 
 int QED_IWARP_MPA_PKT_UNALIGNED ; 
 int /*<<< orphan*/  QED_LL2_TX_DEST_LB ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  memset (struct qed_ll2_tx_pkt_info*,int /*<<< orphan*/ ,int) ; 
 int qed_ll2_prepare_tx_packet (struct qed_hwfn*,int /*<<< orphan*/ ,struct qed_ll2_tx_pkt_info*,int) ; 
 int qed_ll2_set_fragment_of_tx_packet (struct qed_hwfn*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
qed_iwarp_send_fpdu(struct qed_hwfn *p_hwfn,
		    struct qed_iwarp_fpdu *fpdu,
		    struct unaligned_opaque_data *curr_pkt,
		    struct qed_iwarp_ll2_buff *buf,
		    u16 tcp_payload_size, enum qed_iwarp_mpa_pkt_type pkt_type)
{
	struct qed_ll2_tx_pkt_info tx_pkt;
	u8 ll2_handle;
	int rc;

	memset(&tx_pkt, 0, sizeof(tx_pkt));

	/* An unaligned packet means it's split over two tcp segments. So the
	 * complete packet requires 3 bds, one for the header, one for the
	 * part of the fpdu of the first tcp segment, and the last fragment
	 * will point to the remainder of the fpdu. A packed pdu, requires only
	 * two bds, one for the header and one for the data.
	 */
	tx_pkt.num_of_bds = (pkt_type == QED_IWARP_MPA_PKT_UNALIGNED) ? 3 : 2;
	tx_pkt.tx_dest = QED_LL2_TX_DEST_LB;
	tx_pkt.l4_hdr_offset_w = fpdu->pkt_hdr_size >> 2; /* offset in words */

	/* Send the mpa_buf only with the last fpdu (in case of packed) */
	if (pkt_type == QED_IWARP_MPA_PKT_UNALIGNED ||
	    tcp_payload_size <= fpdu->fpdu_length)
		tx_pkt.cookie = fpdu->mpa_buf;

	tx_pkt.first_frag = fpdu->pkt_hdr;
	tx_pkt.first_frag_len = fpdu->pkt_hdr_size;
	tx_pkt.enable_ip_cksum = true;
	tx_pkt.enable_l4_cksum = true;
	tx_pkt.calc_ip_len = true;
	/* vlan overload with enum iwarp_ll2_tx_queues */
	tx_pkt.vlan = IWARP_LL2_ALIGNED_TX_QUEUE;

	/* special case of unaligned packet and not packed, need to send
	 * both buffers as cookie to release.
	 */
	if (tcp_payload_size == fpdu->incomplete_bytes)
		fpdu->mpa_buf->piggy_buf = buf;

	ll2_handle = p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle;

	/* Set first fragment to header */
	rc = qed_ll2_prepare_tx_packet(p_hwfn, ll2_handle, &tx_pkt, true);
	if (rc)
		goto out;

	/* Set second fragment to first part of packet */
	rc = qed_ll2_set_fragment_of_tx_packet(p_hwfn, ll2_handle,
					       fpdu->mpa_frag,
					       fpdu->mpa_frag_len);
	if (rc)
		goto out;

	if (!fpdu->incomplete_bytes)
		goto out;

	/* Set third fragment to second part of the packet */
	rc = qed_ll2_set_fragment_of_tx_packet(p_hwfn,
					       ll2_handle,
					       buf->data_phys_addr +
					       curr_pkt->first_mpa_offset,
					       fpdu->incomplete_bytes);
out:
	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "MPA_ALIGN: Sent FPDU num_bds=%d first_frag_len=%x, mpa_frag_len=0x%x, incomplete_bytes:0x%x rc=%d\n",
		   tx_pkt.num_of_bds,
		   tx_pkt.first_frag_len,
		   fpdu->mpa_frag_len,
		   fpdu->incomplete_bytes, rc);

	return rc;
}