#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_req_mgr_handle {size_t req_queue_head; int req_queue_tail; unsigned int max_used_sw_slots; unsigned int q_free_slots; struct cc_hw_desc compl_desc; struct cc_crypto_req* req_queue; } ;
struct cc_drvdata {struct cc_req_mgr_handle* request_mgr_handle; } ;
struct cc_crypto_req {int /*<<< orphan*/  ivgen_size; int /*<<< orphan*/  ivgen_dma_addr_len; int /*<<< orphan*/ * ivgen_dma_addr; } ;

/* Variables and functions */
 int CC_IVPOOL_SEQ_LEN ; 
 int EINPROGRESS ; 
 int MAX_REQUEST_QUEUE_SIZE ; 
 int cc_get_iv (struct cc_drvdata*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  enqueue_seq (struct cc_drvdata*,struct cc_hw_desc*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int cc_do_send_request(struct cc_drvdata *drvdata,
			      struct cc_crypto_req *cc_req,
			      struct cc_hw_desc *desc, unsigned int len,
				bool add_comp, bool ivgen)
{
	struct cc_req_mgr_handle *req_mgr_h = drvdata->request_mgr_handle;
	unsigned int used_sw_slots;
	unsigned int iv_seq_len = 0;
	unsigned int total_seq_len = len; /*initial sequence length*/
	struct cc_hw_desc iv_seq[CC_IVPOOL_SEQ_LEN];
	struct device *dev = drvdata_to_dev(drvdata);
	int rc;

	if (ivgen) {
		dev_dbg(dev, "Acquire IV from pool into %d DMA addresses %pad, %pad, %pad, IV-size=%u\n",
			cc_req->ivgen_dma_addr_len,
			&cc_req->ivgen_dma_addr[0],
			&cc_req->ivgen_dma_addr[1],
			&cc_req->ivgen_dma_addr[2],
			cc_req->ivgen_size);

		/* Acquire IV from pool */
		rc = cc_get_iv(drvdata, cc_req->ivgen_dma_addr,
			       cc_req->ivgen_dma_addr_len,
			       cc_req->ivgen_size, iv_seq, &iv_seq_len);

		if (rc) {
			dev_err(dev, "Failed to generate IV (rc=%d)\n", rc);
			return rc;
		}

		total_seq_len += iv_seq_len;
	}

	used_sw_slots = ((req_mgr_h->req_queue_head -
			  req_mgr_h->req_queue_tail) &
			 (MAX_REQUEST_QUEUE_SIZE - 1));
	if (used_sw_slots > req_mgr_h->max_used_sw_slots)
		req_mgr_h->max_used_sw_slots = used_sw_slots;

	/* Enqueue request - must be locked with HW lock*/
	req_mgr_h->req_queue[req_mgr_h->req_queue_head] = *cc_req;
	req_mgr_h->req_queue_head = (req_mgr_h->req_queue_head + 1) &
				    (MAX_REQUEST_QUEUE_SIZE - 1);
	/* TODO: Use circ_buf.h ? */

	dev_dbg(dev, "Enqueue request head=%u\n", req_mgr_h->req_queue_head);

	/*
	 * We are about to push command to the HW via the command registers
	 * that may refernece hsot memory. We need to issue a memory barrier
	 * to make sure there are no outstnading memory writes
	 */
	wmb();

	/* STAT_PHASE_4: Push sequence */
	if (ivgen)
		enqueue_seq(drvdata, iv_seq, iv_seq_len);

	enqueue_seq(drvdata, desc, len);

	if (add_comp) {
		enqueue_seq(drvdata, &req_mgr_h->compl_desc, 1);
		total_seq_len++;
	}

	if (req_mgr_h->q_free_slots < total_seq_len) {
		/* This situation should never occur. Maybe indicating problem
		 * with resuming power. Set the free slot count to 0 and hope
		 * for the best.
		 */
		dev_err(dev, "HW free slot count mismatch.");
		req_mgr_h->q_free_slots = 0;
	} else {
		/* Update the free slots in HW queue */
		req_mgr_h->q_free_slots -= total_seq_len;
	}

	/* Operation still in process */
	return -EINPROGRESS;
}