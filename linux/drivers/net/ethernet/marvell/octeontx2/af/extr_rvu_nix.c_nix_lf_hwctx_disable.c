#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct rvu_pfvf {unsigned long* cq_bmap; unsigned long* sq_bmap; unsigned long* rq_bmap; TYPE_11__* rq_ctx; TYPE_8__* sq_ctx; TYPE_5__* cq_ctx; } ;
struct rvu {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int ena; } ;
struct TYPE_22__ {scalar_t__ ena; } ;
struct TYPE_20__ {int ena; } ;
struct TYPE_19__ {scalar_t__ ena; } ;
struct TYPE_17__ {int ena; } ;
struct TYPE_16__ {scalar_t__ ena; } ;
struct TYPE_14__ {int /*<<< orphan*/  pcifunc; } ;
struct nix_aq_enq_req {scalar_t__ ctype; int qidx; int /*<<< orphan*/  op; TYPE_10__ rq_mask; TYPE_9__ rq; TYPE_7__ sq_mask; TYPE_6__ sq; TYPE_4__ cq_mask; TYPE_3__ cq; TYPE_1__ hdr; } ;
struct TYPE_15__ {int /*<<< orphan*/  pcifunc; } ;
struct hwctx_disable_req {scalar_t__ ctype; TYPE_2__ hdr; } ;
struct TYPE_21__ {int qsize; } ;
struct TYPE_18__ {int qsize; } ;
struct TYPE_13__ {int qsize; } ;

/* Variables and functions */
 int NIX_AF_ERR_AQ_ENQUEUE ; 
 scalar_t__ NIX_AQ_CTYPE_CQ ; 
 scalar_t__ NIX_AQ_CTYPE_RQ ; 
 scalar_t__ NIX_AQ_CTYPE_SQ ; 
 int /*<<< orphan*/  NIX_AQ_INSTOP_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct nix_aq_enq_req*,int /*<<< orphan*/ ,int) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 
 int rvu_nix_aq_enq_inst (struct rvu*,struct nix_aq_enq_req*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

__attribute__((used)) static int nix_lf_hwctx_disable(struct rvu *rvu, struct hwctx_disable_req *req)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, req->hdr.pcifunc);
	struct nix_aq_enq_req aq_req;
	unsigned long *bmap;
	int qidx, q_cnt = 0;
	int err = 0, rc;

	if (!pfvf->cq_ctx || !pfvf->sq_ctx || !pfvf->rq_ctx)
		return NIX_AF_ERR_AQ_ENQUEUE;

	memset(&aq_req, 0, sizeof(struct nix_aq_enq_req));
	aq_req.hdr.pcifunc = req->hdr.pcifunc;

	if (req->ctype == NIX_AQ_CTYPE_CQ) {
		aq_req.cq.ena = 0;
		aq_req.cq_mask.ena = 1;
		q_cnt = pfvf->cq_ctx->qsize;
		bmap = pfvf->cq_bmap;
	}
	if (req->ctype == NIX_AQ_CTYPE_SQ) {
		aq_req.sq.ena = 0;
		aq_req.sq_mask.ena = 1;
		q_cnt = pfvf->sq_ctx->qsize;
		bmap = pfvf->sq_bmap;
	}
	if (req->ctype == NIX_AQ_CTYPE_RQ) {
		aq_req.rq.ena = 0;
		aq_req.rq_mask.ena = 1;
		q_cnt = pfvf->rq_ctx->qsize;
		bmap = pfvf->rq_bmap;
	}

	aq_req.ctype = req->ctype;
	aq_req.op = NIX_AQ_INSTOP_WRITE;

	for (qidx = 0; qidx < q_cnt; qidx++) {
		if (!test_bit(qidx, bmap))
			continue;
		aq_req.qidx = qidx;
		rc = rvu_nix_aq_enq_inst(rvu, &aq_req, NULL);
		if (rc) {
			err = rc;
			dev_err(rvu->dev, "Failed to disable %s:%d context\n",
				(req->ctype == NIX_AQ_CTYPE_CQ) ?
				"CQ" : ((req->ctype == NIX_AQ_CTYPE_RQ) ?
				"RQ" : "SQ"), qidx);
		}
	}

	return err;
}