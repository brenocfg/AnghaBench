#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct skcipher_request {int dummy; } ;
struct TYPE_22__ {int ctxl; int /*<<< orphan*/  arg; int /*<<< orphan*/  ctxc; } ;
struct TYPE_23__ {TYPE_7__ s; } ;
struct se_crypto_request {int /*<<< orphan*/  gph; int /*<<< orphan*/  opcode; TYPE_8__ ctrl; scalar_t__ ctx_handle; int /*<<< orphan*/  gfp; int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {void* rptr; int /*<<< orphan*/  ssz; } ;
struct TYPE_14__ {TYPE_1__ s; void** value; } ;
struct TYPE_24__ {int ctxl; void* ctxp; int /*<<< orphan*/  opcode; int /*<<< orphan*/  arg; int /*<<< orphan*/  ctxc; scalar_t__ destport; int /*<<< orphan*/  uddl; } ;
struct TYPE_13__ {TYPE_9__ s; void** value; } ;
struct TYPE_19__ {int g; scalar_t__ fsz; scalar_t__ tlen; int /*<<< orphan*/  ssz; int /*<<< orphan*/  gsz; } ;
struct TYPE_21__ {void* value; TYPE_4__ s; } ;
struct TYPE_15__ {scalar_t__* fdata; TYPE_11__ slc; TYPE_10__ irh; TYPE_6__ ih; void* dptr0; } ;
struct TYPE_18__ {void* dma; int /*<<< orphan*/  map_bufs_cnt; } ;
struct TYPE_20__ {scalar_t__ total_bytes; int /*<<< orphan*/  map_bufs_cnt; void* dma; } ;
struct TYPE_17__ {int /*<<< orphan*/  completion; int /*<<< orphan*/  orh; } ;
struct nitrox_softreq {TYPE_12__ instr; TYPE_3__ out; TYPE_5__ in; int /*<<< orphan*/ * cmdq; TYPE_2__ resp; int /*<<< orphan*/  status; struct skcipher_request* skreq; int /*<<< orphan*/  callback; int /*<<< orphan*/  gfp; int /*<<< orphan*/  flags; struct nitrox_device* ndev; } ;
struct nitrox_device {int nr_queues; int /*<<< orphan*/ * pkt_cmdqs; } ;
struct gphdr {int dummy; } ;
struct ctx_hdr {void* ctx_dma; } ;
typedef  void* dma_addr_t ;
typedef  int /*<<< orphan*/  completion_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ FDATA_SIZE ; 
 int /*<<< orphan*/  MIN_UDD_LEN ; 
 int /*<<< orphan*/  PENDING_SIG ; 
 int /*<<< orphan*/  REQ_NOT_POSTED ; 
 scalar_t__ SOLICIT_BASE_DPORT ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (void*) ; 
 int /*<<< orphan*/  kfree (struct nitrox_softreq*) ; 
 struct nitrox_softreq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nitrox_enqueue_request (struct nitrox_softreq*) ; 
 int /*<<< orphan*/  nitrox_ready (struct nitrox_device*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  softreq_destroy (struct nitrox_softreq*) ; 
 int softreq_map_iobuf (struct nitrox_softreq*,struct se_crypto_request*) ; 

int nitrox_process_se_request(struct nitrox_device *ndev,
			      struct se_crypto_request *req,
			      completion_t callback,
			      struct skcipher_request *skreq)
{
	struct nitrox_softreq *sr;
	dma_addr_t ctx_handle = 0;
	int qno, ret = 0;

	if (!nitrox_ready(ndev))
		return -ENODEV;

	sr = kzalloc(sizeof(*sr), req->gfp);
	if (!sr)
		return -ENOMEM;

	sr->ndev = ndev;
	sr->flags = req->flags;
	sr->gfp = req->gfp;
	sr->callback = callback;
	sr->skreq = skreq;

	atomic_set(&sr->status, REQ_NOT_POSTED);

	WRITE_ONCE(sr->resp.orh, PENDING_SIG);
	WRITE_ONCE(sr->resp.completion, PENDING_SIG);

	ret = softreq_map_iobuf(sr, req);
	if (ret) {
		kfree(sr);
		return ret;
	}

	/* get the context handle */
	if (req->ctx_handle) {
		struct ctx_hdr *hdr;
		u8 *ctx_ptr;

		ctx_ptr = (u8 *)(uintptr_t)req->ctx_handle;
		hdr = (struct ctx_hdr *)(ctx_ptr - sizeof(struct ctx_hdr));
		ctx_handle = hdr->ctx_dma;
	}

	/* select the queue */
	qno = smp_processor_id() % ndev->nr_queues;

	sr->cmdq = &ndev->pkt_cmdqs[qno];

	/*
	 * 64-Byte Instruction Format
	 *
	 *  ----------------------
	 *  |      DPTR0         | 8 bytes
	 *  ----------------------
	 *  |  PKT_IN_INSTR_HDR  | 8 bytes
	 *  ----------------------
	 *  |    PKT_IN_HDR      | 16 bytes
	 *  ----------------------
	 *  |    SLC_INFO        | 16 bytes
	 *  ----------------------
	 *  |   Front data       | 16 bytes
	 *  ----------------------
	 */

	/* fill the packet instruction */
	/* word 0 */
	sr->instr.dptr0 = cpu_to_be64(sr->in.dma);

	/* word 1 */
	sr->instr.ih.value = 0;
	sr->instr.ih.s.g = 1;
	sr->instr.ih.s.gsz = sr->in.map_bufs_cnt;
	sr->instr.ih.s.ssz = sr->out.map_bufs_cnt;
	sr->instr.ih.s.fsz = FDATA_SIZE + sizeof(struct gphdr);
	sr->instr.ih.s.tlen = sr->instr.ih.s.fsz + sr->in.total_bytes;
	sr->instr.ih.value = cpu_to_be64(sr->instr.ih.value);

	/* word 2 */
	sr->instr.irh.value[0] = 0;
	sr->instr.irh.s.uddl = MIN_UDD_LEN;
	/* context length in 64-bit words */
	sr->instr.irh.s.ctxl = (req->ctrl.s.ctxl / 8);
	/* offset from solicit base port 256 */
	sr->instr.irh.s.destport = SOLICIT_BASE_DPORT + qno;
	sr->instr.irh.s.ctxc = req->ctrl.s.ctxc;
	sr->instr.irh.s.arg = req->ctrl.s.arg;
	sr->instr.irh.s.opcode = req->opcode;
	sr->instr.irh.value[0] = cpu_to_be64(sr->instr.irh.value[0]);

	/* word 3 */
	sr->instr.irh.s.ctxp = cpu_to_be64(ctx_handle);

	/* word 4 */
	sr->instr.slc.value[0] = 0;
	sr->instr.slc.s.ssz = sr->out.map_bufs_cnt;
	sr->instr.slc.value[0] = cpu_to_be64(sr->instr.slc.value[0]);

	/* word 5 */
	sr->instr.slc.s.rptr = cpu_to_be64(sr->out.dma);

	/*
	 * No conversion for front data,
	 * It goes into payload
	 * put GP Header in front data
	 */
	sr->instr.fdata[0] = *((u64 *)&req->gph);
	sr->instr.fdata[1] = 0;

	ret = nitrox_enqueue_request(sr);
	if (ret == -ENOSPC)
		goto send_fail;

	return ret;

send_fail:
	softreq_destroy(sr);
	return ret;
}