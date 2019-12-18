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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int ack_psn; struct resp_res* res; } ;
struct rxe_qp {TYPE_2__ resp; } ;
struct rxe_pkt_info {int mask; scalar_t__ psn; } ;
struct TYPE_6__ {int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {scalar_t__ va_org; scalar_t__ length; scalar_t__ rkey; scalar_t__ resid; scalar_t__ va; } ;
struct resp_res {scalar_t__ cur_psn; scalar_t__ first_psn; int replay; TYPE_3__ atomic; TYPE_1__ read; int /*<<< orphan*/  state; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;

/* Variables and functions */
 int /*<<< orphan*/  AETH_ACK_UNLIMITED ; 
 int BTH_PSN_MASK ; 
 int RESPST_CLEANUP ; 
 int RESPST_READ_REPLY ; 
 int RXE_READ_MASK ; 
 int RXE_SEND_MASK ; 
 int RXE_WRITE_MASK ; 
 scalar_t__ bth_ack (struct rxe_pkt_info*) ; 
 struct resp_res* find_resource (struct rxe_qp*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rdatm_res_state_new ; 
 int /*<<< orphan*/  rdatm_res_state_replay ; 
 scalar_t__ reth_len (struct rxe_pkt_info*) ; 
 scalar_t__ reth_rkey (struct rxe_pkt_info*) ; 
 scalar_t__ reth_va (struct rxe_pkt_info*) ; 
 int rxe_xmit_packet (struct rxe_qp*,struct rxe_pkt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_ack (struct rxe_qp*,struct rxe_pkt_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum resp_states duplicate_request(struct rxe_qp *qp,
					  struct rxe_pkt_info *pkt)
{
	enum resp_states rc;
	u32 prev_psn = (qp->resp.ack_psn - 1) & BTH_PSN_MASK;

	if (pkt->mask & RXE_SEND_MASK ||
	    pkt->mask & RXE_WRITE_MASK) {
		/* SEND. Ack again and cleanup. C9-105. */
		if (bth_ack(pkt))
			send_ack(qp, pkt, AETH_ACK_UNLIMITED, prev_psn);
		rc = RESPST_CLEANUP;
		goto out;
	} else if (pkt->mask & RXE_READ_MASK) {
		struct resp_res *res;

		res = find_resource(qp, pkt->psn);
		if (!res) {
			/* Resource not found. Class D error.  Drop the
			 * request.
			 */
			rc = RESPST_CLEANUP;
			goto out;
		} else {
			/* Ensure this new request is the same as the previous
			 * one or a subset of it.
			 */
			u64 iova = reth_va(pkt);
			u32 resid = reth_len(pkt);

			if (iova < res->read.va_org ||
			    resid > res->read.length ||
			    (iova + resid) > (res->read.va_org +
					      res->read.length)) {
				rc = RESPST_CLEANUP;
				goto out;
			}

			if (reth_rkey(pkt) != res->read.rkey) {
				rc = RESPST_CLEANUP;
				goto out;
			}

			res->cur_psn = pkt->psn;
			res->state = (pkt->psn == res->first_psn) ?
					rdatm_res_state_new :
					rdatm_res_state_replay;
			res->replay = 1;

			/* Reset the resource, except length. */
			res->read.va_org = iova;
			res->read.va = iova;
			res->read.resid = resid;

			/* Replay the RDMA read reply. */
			qp->resp.res = res;
			rc = RESPST_READ_REPLY;
			goto out;
		}
	} else {
		struct resp_res *res;

		/* Find the operation in our list of responder resources. */
		res = find_resource(qp, pkt->psn);
		if (res) {
			skb_get(res->atomic.skb);
			/* Resend the result. */
			rc = rxe_xmit_packet(qp, pkt, res->atomic.skb);
			if (rc) {
				pr_err("Failed resending result. This flow is not handled - skb ignored\n");
				rc = RESPST_CLEANUP;
				goto out;
			}
		}

		/* Resource not found. Class D error. Drop the request. */
		rc = RESPST_CLEANUP;
		goto out;
	}
out:
	return rc;
}