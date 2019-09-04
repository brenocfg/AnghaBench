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
struct unaligned_opaque_data {int cid; int first_mpa_offset; } ;
struct qed_iwarp_ll2_mpa_buf {int /*<<< orphan*/  tcp_payload_len; int /*<<< orphan*/  placement_offset; struct qed_iwarp_ll2_buff* ll2_buf; struct unaligned_opaque_data data; } ;
struct qed_iwarp_ll2_buff {scalar_t__ data; } ;
struct qed_iwarp_fpdu {int /*<<< orphan*/  incomplete_bytes; int /*<<< orphan*/  fpdu_length; } ;
struct qed_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  enum qed_iwarp_mpa_pkt_type { ____Placeholder_qed_iwarp_mpa_pkt_type } qed_iwarp_mpa_pkt_type ;
struct TYPE_3__ {int /*<<< orphan*/  ll2_mpa_handle; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_IWARP_IS_RIGHT_EDGE (struct unaligned_opaque_data*) ; 
#define  QED_IWARP_MPA_PKT_PACKED 130 
#define  QED_IWARP_MPA_PKT_PARTIAL 129 
#define  QED_IWARP_MPA_PKT_UNALIGNED 128 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  memset (struct qed_iwarp_fpdu*,int /*<<< orphan*/ ,int) ; 
 int qed_iwarp_cp_pkt (struct qed_hwfn*,struct qed_iwarp_fpdu*,struct unaligned_opaque_data*,struct qed_iwarp_ll2_buff*,int /*<<< orphan*/ ) ; 
 struct qed_iwarp_fpdu* qed_iwarp_get_curr_fpdu (struct qed_hwfn*,int) ; 
 int /*<<< orphan*/  qed_iwarp_init_fpdu (struct qed_iwarp_ll2_buff*,struct qed_iwarp_fpdu*,struct unaligned_opaque_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iwarp_ll2_post_rx (struct qed_hwfn*,struct qed_iwarp_ll2_buff*,int /*<<< orphan*/ ) ; 
 int qed_iwarp_mpa_classify (struct qed_hwfn*,struct qed_iwarp_fpdu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qed_iwarp_send_fpdu (struct qed_hwfn*,struct qed_iwarp_fpdu*,struct unaligned_opaque_data*,struct qed_iwarp_ll2_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_iwarp_update_fpdu_length (struct qed_hwfn*,struct qed_iwarp_fpdu*,int /*<<< orphan*/ *) ; 
 int qed_iwarp_win_right_edge (struct qed_hwfn*,struct qed_iwarp_fpdu*) ; 

__attribute__((used)) static int
qed_iwarp_process_mpa_pkt(struct qed_hwfn *p_hwfn,
			  struct qed_iwarp_ll2_mpa_buf *mpa_buf)
{
	struct unaligned_opaque_data *curr_pkt = &mpa_buf->data;
	struct qed_iwarp_ll2_buff *buf = mpa_buf->ll2_buf;
	enum qed_iwarp_mpa_pkt_type pkt_type;
	struct qed_iwarp_fpdu *fpdu;
	int rc = -EINVAL;
	u8 *mpa_data;

	fpdu = qed_iwarp_get_curr_fpdu(p_hwfn, curr_pkt->cid & 0xffff);
	if (!fpdu) { /* something corrupt with cid, post rx back */
		DP_ERR(p_hwfn, "Invalid cid, drop and post back to rx cid=%x\n",
		       curr_pkt->cid);
		goto err;
	}

	do {
		mpa_data = ((u8 *)(buf->data) + curr_pkt->first_mpa_offset);

		pkt_type = qed_iwarp_mpa_classify(p_hwfn, fpdu,
						  mpa_buf->tcp_payload_len,
						  mpa_data);

		switch (pkt_type) {
		case QED_IWARP_MPA_PKT_PARTIAL:
			qed_iwarp_init_fpdu(buf, fpdu,
					    curr_pkt,
					    mpa_buf->tcp_payload_len,
					    mpa_buf->placement_offset);

			if (!QED_IWARP_IS_RIGHT_EDGE(curr_pkt)) {
				mpa_buf->tcp_payload_len = 0;
				break;
			}

			rc = qed_iwarp_win_right_edge(p_hwfn, fpdu);

			if (rc) {
				DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
					   "Can't send FPDU:reset rc=%d\n", rc);
				memset(fpdu, 0, sizeof(*fpdu));
				break;
			}

			mpa_buf->tcp_payload_len = 0;
			break;
		case QED_IWARP_MPA_PKT_PACKED:
			qed_iwarp_init_fpdu(buf, fpdu,
					    curr_pkt,
					    mpa_buf->tcp_payload_len,
					    mpa_buf->placement_offset);

			rc = qed_iwarp_send_fpdu(p_hwfn, fpdu, curr_pkt, buf,
						 mpa_buf->tcp_payload_len,
						 pkt_type);
			if (rc) {
				DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
					   "Can't send FPDU:reset rc=%d\n", rc);
				memset(fpdu, 0, sizeof(*fpdu));
				break;
			}

			mpa_buf->tcp_payload_len -= fpdu->fpdu_length;
			curr_pkt->first_mpa_offset += fpdu->fpdu_length;
			break;
		case QED_IWARP_MPA_PKT_UNALIGNED:
			qed_iwarp_update_fpdu_length(p_hwfn, fpdu, mpa_data);
			if (mpa_buf->tcp_payload_len < fpdu->incomplete_bytes) {
				/* special handling of fpdu split over more
				 * than 2 segments
				 */
				if (QED_IWARP_IS_RIGHT_EDGE(curr_pkt)) {
					rc = qed_iwarp_win_right_edge(p_hwfn,
								      fpdu);
					/* packet will be re-processed later */
					if (rc)
						return rc;
				}

				rc = qed_iwarp_cp_pkt(p_hwfn, fpdu, curr_pkt,
						      buf,
						      mpa_buf->tcp_payload_len);
				if (rc) /* packet will be re-processed later */
					return rc;

				mpa_buf->tcp_payload_len = 0;
				break;
			}

			rc = qed_iwarp_send_fpdu(p_hwfn, fpdu, curr_pkt, buf,
						 mpa_buf->tcp_payload_len,
						 pkt_type);
			if (rc) {
				DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
					   "Can't send FPDU:delay rc=%d\n", rc);
				/* don't reset fpdu -> we need it for next
				 * classify
				 */
				break;
			}

			mpa_buf->tcp_payload_len -= fpdu->incomplete_bytes;
			curr_pkt->first_mpa_offset += fpdu->incomplete_bytes;
			/* The framed PDU was sent - no more incomplete bytes */
			fpdu->incomplete_bytes = 0;
			break;
		}
	} while (mpa_buf->tcp_payload_len && !rc);

	return rc;

err:
	qed_iwarp_ll2_post_rx(p_hwfn,
			      buf,
			      p_hwfn->p_rdma_info->iwarp.ll2_mpa_handle);
	return rc;
}