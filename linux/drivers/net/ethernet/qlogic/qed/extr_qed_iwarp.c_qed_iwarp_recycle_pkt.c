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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tx_pkt ;
struct qed_ll2_tx_pkt_info {int num_of_bds; int l4_hdr_offset_w; int first_frag_len; scalar_t__ first_frag; struct qed_iwarp_ll2_buff* cookie; int /*<<< orphan*/  tx_dest; } ;
struct qed_iwarp_ll2_buff {int /*<<< orphan*/ * piggy_buf; } ;
struct qed_iwarp_fpdu {int pkt_hdr_size; scalar_t__ pkt_hdr; } ;
struct qed_hwfn {TYPE_2__* p_rdma_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  ll2_mpa_handle; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int /*<<< orphan*/  QED_LL2_TX_DEST_DROP ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  memset (struct qed_ll2_tx_pkt_info*,int /*<<< orphan*/ ,int) ; 
 int qed_ll2_prepare_tx_packet (struct qed_hwfn*,int /*<<< orphan*/ ,struct qed_ll2_tx_pkt_info*,int) ; 

__attribute__((used)) static int
qed_iwarp_recycle_pkt(struct qed_hwfn *p_hwfn,
		      struct qed_iwarp_fpdu *fpdu,
		      struct qed_iwarp_ll2_buff *buf)
{
	struct qed_ll2_tx_pkt_info tx_pkt;
	u8 ll2_handle;
	int rc;

	memset(&tx_pkt, 0, sizeof(tx_pkt));
	tx_pkt.num_of_bds = 1;
	tx_pkt.tx_dest = QED_LL2_TX_DEST_DROP;
	tx_pkt.l4_hdr_offset_w = fpdu->pkt_hdr_size >> 2;
	tx_pkt.first_frag = fpdu->pkt_hdr;
	tx_pkt.first_frag_len = fpdu->pkt_hdr_size;
	buf->piggy_buf = NULL;
	tx_pkt.cookie = buf;

	ll2_handle = p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle;

	rc = qed_ll2_prepare_tx_packet(p_hwfn, ll2_handle, &tx_pkt, true);
	if (rc)
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Can't drop packet rc=%d\n", rc);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "MPA_ALIGN: send drop tx packet [%lx, 0x%x], buf=%p, rc=%d\n",
		   (unsigned long int)tx_pkt.first_frag,
		   tx_pkt.first_frag_len, buf, rc);

	return rc;
}