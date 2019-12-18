#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_9__ {int npkts; int /*<<< orphan*/  ctrl; scalar_t__ iov_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  ver_tid_offset; int /*<<< orphan*/ * swdata; } ;
struct sdma_req_info {int iov_len; int comp_idx; int /*<<< orphan*/ * lrh; scalar_t__ iov_base; TYPE_1__ kdeth; int /*<<< orphan*/ * bth; scalar_t__* pbc; int /*<<< orphan*/  npkts; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  fragsize; } ;
struct user_sdma_request {int data_iovs; int ahg_idx; int seqcomp; int seqsubmitted; int* tids; int tidoffset; int n_tids; TYPE_4__ info; int /*<<< orphan*/  sde; struct sdma_req_info hdr; scalar_t__ tididx; scalar_t__ data_len; TYPE_3__* iovs; int /*<<< orphan*/  koffset; int /*<<< orphan*/  txps; scalar_t__ has_error; scalar_t__ seqnum; scalar_t__ sent; scalar_t__ iov_idx; struct hfi1_user_sdma_comp_q* cq; struct hfi1_user_sdma_pkt_q* pq; } ;
struct iovec {int iov_len; int comp_idx; int /*<<< orphan*/ * lrh; scalar_t__ iov_base; TYPE_1__ kdeth; int /*<<< orphan*/ * bth; scalar_t__* pbc; int /*<<< orphan*/  npkts; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  fragsize; } ;
struct TYPE_7__ {int /*<<< orphan*/  wait_dma; } ;
struct hfi1_user_sdma_pkt_q {scalar_t__ state; TYPE_2__ busy; int /*<<< orphan*/  n_reqs; struct user_sdma_request* reqs; int /*<<< orphan*/  req_in_use; struct hfi1_devdata* dd; } ;
struct hfi1_user_sdma_comp_q {int dummy; } ;
struct hfi1_filedata {scalar_t__ subctxt; struct hfi1_user_sdma_comp_q* cq; struct hfi1_user_sdma_pkt_q* pq; struct hfi1_ctxtdata* uctxt; } ;
struct hfi1_devdata {TYPE_5__* pport; int /*<<< orphan*/  unit; } ;
struct hfi1_ctxtdata {scalar_t__ ctxt; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_10__ {int vls_operational; } ;
struct TYPE_8__ {TYPE_4__ iov; int /*<<< orphan*/  list; scalar_t__ offset; } ;

/* Variables and functions */
 int EBADSLT ; 
 int EBUSY ; 
 int ECOMM ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ EXPECTED ; 
 scalar_t__ HFI1_CAP_IS_USET (int /*<<< orphan*/ ) ; 
 int HFI1_LRH_GRH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int*) ; 
 int KDETH_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KDETH_OM_LARGE ; 
 int KDETH_OM_SMALL ; 
 int MAX_TID_PAIR_ENTRIES ; 
 int MAX_VECTORS_PER_REQ ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  OM ; 
 int /*<<< orphan*/  PKEY_CHECK_INVALID ; 
 int PTR_ERR (int*) ; 
 int /*<<< orphan*/  QUEUED ; 
 int /*<<< orphan*/  SDMA ; 
 int /*<<< orphan*/  SDMA_AHG ; 
 int /*<<< orphan*/  SDMA_DBG (struct user_sdma_request*,char*,...) ; 
 int /*<<< orphan*/  SDMA_IOWAIT_TIMEOUT ; 
 scalar_t__ SDMA_PKT_Q_ACTIVE ; 
 int /*<<< orphan*/  STATIC_RATE_CTRL ; 
 int USER_OPCODE_CHECK_MASK ; 
 int USER_OPCODE_CHECK_VAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int copy_from_user (struct sdma_req_info*,scalar_t__,int) ; 
 int dlid_to_selector (int) ; 
 scalar_t__ egress_pkey_check (TYPE_5__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,...) ; 
 int hfi1_sdma_comp_ring_size ; 
 int initial_pkt_count ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,struct sdma_req_info*,int) ; 
 int* memdup_user (scalar_t__,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int pin_vector_pages (struct user_sdma_request*,TYPE_3__*) ; 
 int /*<<< orphan*/  pq_update (struct hfi1_user_sdma_pkt_q*) ; 
 int req_iovcnt (int /*<<< orphan*/ ) ; 
 scalar_t__ req_opcode (int /*<<< orphan*/ ) ; 
 int sc_to_vlt (struct hfi1_devdata*,int) ; 
 int sdma_ahg_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_select_user_engine (struct hfi1_devdata*,int,int) ; 
 int /*<<< orphan*/  set_comp_state (struct hfi1_user_sdma_pkt_q*,struct hfi1_user_sdma_comp_q*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_user_data_length (struct hfi1_devdata*,scalar_t__,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_user_initial_tidoffset (struct hfi1_devdata*,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_user_process_request (struct hfi1_devdata*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_user_reqinfo (struct hfi1_devdata*,scalar_t__,scalar_t__,int*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  user_sdma_free_request (struct user_sdma_request*,int) ; 
 int user_sdma_send_pkts (struct user_sdma_request*,int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int hfi1_user_sdma_process_request(struct hfi1_filedata *fd,
				   struct iovec *iovec, unsigned long dim,
				   unsigned long *count)
{
	int ret = 0, i;
	struct hfi1_ctxtdata *uctxt = fd->uctxt;
	struct hfi1_user_sdma_pkt_q *pq = fd->pq;
	struct hfi1_user_sdma_comp_q *cq = fd->cq;
	struct hfi1_devdata *dd = pq->dd;
	unsigned long idx = 0;
	u8 pcount = initial_pkt_count;
	struct sdma_req_info info;
	struct user_sdma_request *req;
	u8 opcode, sc, vl;
	u16 pkey;
	u32 slid;
	u16 dlid;
	u32 selector;

	if (iovec[idx].iov_len < sizeof(info) + sizeof(req->hdr)) {
		hfi1_cdbg(
		   SDMA,
		   "[%u:%u:%u] First vector not big enough for header %lu/%lu",
		   dd->unit, uctxt->ctxt, fd->subctxt,
		   iovec[idx].iov_len, sizeof(info) + sizeof(req->hdr));
		return -EINVAL;
	}
	ret = copy_from_user(&info, iovec[idx].iov_base, sizeof(info));
	if (ret) {
		hfi1_cdbg(SDMA, "[%u:%u:%u] Failed to copy info QW (%d)",
			  dd->unit, uctxt->ctxt, fd->subctxt, ret);
		return -EFAULT;
	}

	trace_hfi1_sdma_user_reqinfo(dd, uctxt->ctxt, fd->subctxt,
				     (u16 *)&info);
	if (info.comp_idx >= hfi1_sdma_comp_ring_size) {
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Invalid comp index",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx);
		return -EINVAL;
	}

	/*
	 * Sanity check the header io vector count.  Need at least 1 vector
	 * (header) and cannot be larger than the actual io vector count.
	 */
	if (req_iovcnt(info.ctrl) < 1 || req_iovcnt(info.ctrl) > dim) {
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Invalid iov count %d, dim %ld",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx,
			  req_iovcnt(info.ctrl), dim);
		return -EINVAL;
	}

	if (!info.fragsize) {
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Request does not specify fragsize",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx);
		return -EINVAL;
	}

	/* Try to claim the request. */
	if (test_and_set_bit(info.comp_idx, pq->req_in_use)) {
		hfi1_cdbg(SDMA, "[%u:%u:%u] Entry %u is in use",
			  dd->unit, uctxt->ctxt, fd->subctxt,
			  info.comp_idx);
		return -EBADSLT;
	}
	/*
	 * All safety checks have been done and this request has been claimed.
	 */
	trace_hfi1_sdma_user_process_request(dd, uctxt->ctxt, fd->subctxt,
					     info.comp_idx);
	req = pq->reqs + info.comp_idx;
	req->data_iovs = req_iovcnt(info.ctrl) - 1; /* subtract header vector */
	req->data_len  = 0;
	req->pq = pq;
	req->cq = cq;
	req->ahg_idx = -1;
	req->iov_idx = 0;
	req->sent = 0;
	req->seqnum = 0;
	req->seqcomp = 0;
	req->seqsubmitted = 0;
	req->tids = NULL;
	req->has_error = 0;
	INIT_LIST_HEAD(&req->txps);

	memcpy(&req->info, &info, sizeof(info));

	/* The request is initialized, count it */
	atomic_inc(&pq->n_reqs);

	if (req_opcode(info.ctrl) == EXPECTED) {
		/* expected must have a TID info and at least one data vector */
		if (req->data_iovs < 2) {
			SDMA_DBG(req,
				 "Not enough vectors for expected request");
			ret = -EINVAL;
			goto free_req;
		}
		req->data_iovs--;
	}

	if (!info.npkts || req->data_iovs > MAX_VECTORS_PER_REQ) {
		SDMA_DBG(req, "Too many vectors (%u/%u)", req->data_iovs,
			 MAX_VECTORS_PER_REQ);
		ret = -EINVAL;
		goto free_req;
	}
	/* Copy the header from the user buffer */
	ret = copy_from_user(&req->hdr, iovec[idx].iov_base + sizeof(info),
			     sizeof(req->hdr));
	if (ret) {
		SDMA_DBG(req, "Failed to copy header template (%d)", ret);
		ret = -EFAULT;
		goto free_req;
	}

	/* If Static rate control is not enabled, sanitize the header. */
	if (!HFI1_CAP_IS_USET(STATIC_RATE_CTRL))
		req->hdr.pbc[2] = 0;

	/* Validate the opcode. Do not trust packets from user space blindly. */
	opcode = (be32_to_cpu(req->hdr.bth[0]) >> 24) & 0xff;
	if ((opcode & USER_OPCODE_CHECK_MASK) !=
	     USER_OPCODE_CHECK_VAL) {
		SDMA_DBG(req, "Invalid opcode (%d)", opcode);
		ret = -EINVAL;
		goto free_req;
	}
	/*
	 * Validate the vl. Do not trust packets from user space blindly.
	 * VL comes from PBC, SC comes from LRH, and the VL needs to
	 * match the SC look up.
	 */
	vl = (le16_to_cpu(req->hdr.pbc[0]) >> 12) & 0xF;
	sc = (((be16_to_cpu(req->hdr.lrh[0]) >> 12) & 0xF) |
	      (((le16_to_cpu(req->hdr.pbc[1]) >> 14) & 0x1) << 4));
	if (vl >= dd->pport->vls_operational ||
	    vl != sc_to_vlt(dd, sc)) {
		SDMA_DBG(req, "Invalid SC(%u)/VL(%u)", sc, vl);
		ret = -EINVAL;
		goto free_req;
	}

	/* Checking P_KEY for requests from user-space */
	pkey = (u16)be32_to_cpu(req->hdr.bth[0]);
	slid = be16_to_cpu(req->hdr.lrh[3]);
	if (egress_pkey_check(dd->pport, slid, pkey, sc, PKEY_CHECK_INVALID)) {
		ret = -EINVAL;
		goto free_req;
	}

	/*
	 * Also should check the BTH.lnh. If it says the next header is GRH then
	 * the RXE parsing will be off and will land in the middle of the KDETH
	 * or miss it entirely.
	 */
	if ((be16_to_cpu(req->hdr.lrh[0]) & 0x3) == HFI1_LRH_GRH) {
		SDMA_DBG(req, "User tried to pass in a GRH");
		ret = -EINVAL;
		goto free_req;
	}

	req->koffset = le32_to_cpu(req->hdr.kdeth.swdata[6]);
	/*
	 * Calculate the initial TID offset based on the values of
	 * KDETH.OFFSET and KDETH.OM that are passed in.
	 */
	req->tidoffset = KDETH_GET(req->hdr.kdeth.ver_tid_offset, OFFSET) *
		(KDETH_GET(req->hdr.kdeth.ver_tid_offset, OM) ?
		 KDETH_OM_LARGE : KDETH_OM_SMALL);
	trace_hfi1_sdma_user_initial_tidoffset(dd, uctxt->ctxt, fd->subctxt,
					       info.comp_idx, req->tidoffset);
	idx++;

	/* Save all the IO vector structures */
	for (i = 0; i < req->data_iovs; i++) {
		req->iovs[i].offset = 0;
		INIT_LIST_HEAD(&req->iovs[i].list);
		memcpy(&req->iovs[i].iov,
		       iovec + idx++,
		       sizeof(req->iovs[i].iov));
		ret = pin_vector_pages(req, &req->iovs[i]);
		if (ret) {
			req->data_iovs = i;
			goto free_req;
		}
		req->data_len += req->iovs[i].iov.iov_len;
	}
	trace_hfi1_sdma_user_data_length(dd, uctxt->ctxt, fd->subctxt,
					 info.comp_idx, req->data_len);
	if (pcount > req->info.npkts)
		pcount = req->info.npkts;
	/*
	 * Copy any TID info
	 * User space will provide the TID info only when the
	 * request type is EXPECTED. This is true even if there is
	 * only one packet in the request and the header is already
	 * setup. The reason for the singular TID case is that the
	 * driver needs to perform safety checks.
	 */
	if (req_opcode(req->info.ctrl) == EXPECTED) {
		u16 ntids = iovec[idx].iov_len / sizeof(*req->tids);
		u32 *tmp;

		if (!ntids || ntids > MAX_TID_PAIR_ENTRIES) {
			ret = -EINVAL;
			goto free_req;
		}

		/*
		 * We have to copy all of the tids because they may vary
		 * in size and, therefore, the TID count might not be
		 * equal to the pkt count. However, there is no way to
		 * tell at this point.
		 */
		tmp = memdup_user(iovec[idx].iov_base,
				  ntids * sizeof(*req->tids));
		if (IS_ERR(tmp)) {
			ret = PTR_ERR(tmp);
			SDMA_DBG(req, "Failed to copy %d TIDs (%d)",
				 ntids, ret);
			goto free_req;
		}
		req->tids = tmp;
		req->n_tids = ntids;
		req->tididx = 0;
		idx++;
	}

	dlid = be16_to_cpu(req->hdr.lrh[1]);
	selector = dlid_to_selector(dlid);
	selector += uctxt->ctxt + fd->subctxt;
	req->sde = sdma_select_user_engine(dd, selector, vl);

	if (!req->sde || !sdma_running(req->sde)) {
		ret = -ECOMM;
		goto free_req;
	}

	/* We don't need an AHG entry if the request contains only one packet */
	if (req->info.npkts > 1 && HFI1_CAP_IS_USET(SDMA_AHG))
		req->ahg_idx = sdma_ahg_alloc(req->sde);

	set_comp_state(pq, cq, info.comp_idx, QUEUED, 0);
	pq->state = SDMA_PKT_Q_ACTIVE;
	/* Send the first N packets in the request to buy us some time */
	ret = user_sdma_send_pkts(req, pcount);
	if (unlikely(ret < 0 && ret != -EBUSY))
		goto free_req;

	/*
	 * This is a somewhat blocking send implementation.
	 * The driver will block the caller until all packets of the
	 * request have been submitted to the SDMA engine. However, it
	 * will not wait for send completions.
	 */
	while (req->seqsubmitted != req->info.npkts) {
		ret = user_sdma_send_pkts(req, pcount);
		if (ret < 0) {
			if (ret != -EBUSY)
				goto free_req;
			wait_event_interruptible_timeout(
				pq->busy.wait_dma,
				(pq->state == SDMA_PKT_Q_ACTIVE),
				msecs_to_jiffies(
					SDMA_IOWAIT_TIMEOUT));
		}
	}
	*count += idx;
	return 0;
free_req:
	/*
	 * If the submitted seqsubmitted == npkts, the completion routine
	 * controls the final state.  If sequbmitted < npkts, wait for any
	 * outstanding packets to finish before cleaning up.
	 */
	if (req->seqsubmitted < req->info.npkts) {
		if (req->seqsubmitted)
			wait_event(pq->busy.wait_dma,
				   (req->seqcomp == req->seqsubmitted - 1));
		user_sdma_free_request(req, true);
		pq_update(pq);
		set_comp_state(pq, cq, info.comp_idx, ERROR, ret);
	}
	return ret;
}