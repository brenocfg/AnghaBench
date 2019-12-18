#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rvu_pfvf {unsigned long* pool_bmap; unsigned long* aura_bmap; TYPE_8__* aura_ctx; TYPE_5__* pool_ctx; } ;
struct rvu {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {int ena; } ;
struct TYPE_14__ {scalar_t__ ena; } ;
struct TYPE_12__ {int ena; } ;
struct TYPE_11__ {scalar_t__ ena; } ;
struct TYPE_9__ {int /*<<< orphan*/  pcifunc; } ;
struct npa_aq_enq_req {scalar_t__ ctype; int aura_id; int /*<<< orphan*/  op; TYPE_7__ aura_mask; TYPE_6__ aura; TYPE_4__ pool_mask; TYPE_3__ pool; TYPE_1__ hdr; } ;
struct TYPE_10__ {int /*<<< orphan*/  pcifunc; } ;
struct hwctx_disable_req {scalar_t__ ctype; TYPE_2__ hdr; } ;
struct TYPE_16__ {int qsize; } ;
struct TYPE_13__ {int qsize; } ;

/* Variables and functions */
 int NPA_AF_ERR_AQ_ENQUEUE ; 
 scalar_t__ NPA_AQ_CTYPE_AURA ; 
 scalar_t__ NPA_AQ_CTYPE_POOL ; 
 int /*<<< orphan*/  NPA_AQ_INSTOP_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct npa_aq_enq_req*,int /*<<< orphan*/ ,int) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 
 int rvu_npa_aq_enq_inst (struct rvu*,struct npa_aq_enq_req*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

__attribute__((used)) static int npa_lf_hwctx_disable(struct rvu *rvu, struct hwctx_disable_req *req)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, req->hdr.pcifunc);
	struct npa_aq_enq_req aq_req;
	unsigned long *bmap;
	int id, cnt = 0;
	int err = 0, rc;

	if (!pfvf->pool_ctx || !pfvf->aura_ctx)
		return NPA_AF_ERR_AQ_ENQUEUE;

	memset(&aq_req, 0, sizeof(struct npa_aq_enq_req));
	aq_req.hdr.pcifunc = req->hdr.pcifunc;

	if (req->ctype == NPA_AQ_CTYPE_POOL) {
		aq_req.pool.ena = 0;
		aq_req.pool_mask.ena = 1;
		cnt = pfvf->pool_ctx->qsize;
		bmap = pfvf->pool_bmap;
	} else if (req->ctype == NPA_AQ_CTYPE_AURA) {
		aq_req.aura.ena = 0;
		aq_req.aura_mask.ena = 1;
		cnt = pfvf->aura_ctx->qsize;
		bmap = pfvf->aura_bmap;
	}

	aq_req.ctype = req->ctype;
	aq_req.op = NPA_AQ_INSTOP_WRITE;

	for (id = 0; id < cnt; id++) {
		if (!test_bit(id, bmap))
			continue;
		aq_req.aura_id = id;
		rc = rvu_npa_aq_enq_inst(rvu, &aq_req, NULL);
		if (rc) {
			err = rc;
			dev_err(rvu->dev, "Failed to disable %s:%d context\n",
				(req->ctype == NPA_AQ_CTYPE_AURA) ?
				"Aura" : "Pool", id);
		}
	}

	return err;
}