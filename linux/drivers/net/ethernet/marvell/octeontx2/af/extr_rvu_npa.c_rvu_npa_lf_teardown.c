#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct rvu_pfvf {int dummy; } ;
struct rvu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct hwctx_disable_req {int /*<<< orphan*/  ctype; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPA_AQ_CTYPE_AURA ; 
 int /*<<< orphan*/  NPA_AQ_CTYPE_POOL ; 
 int /*<<< orphan*/  npa_ctx_free (struct rvu*,struct rvu_pfvf*) ; 
 int /*<<< orphan*/  npa_lf_hwctx_disable (struct rvu*,struct hwctx_disable_req*) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 

void rvu_npa_lf_teardown(struct rvu *rvu, u16 pcifunc, int npalf)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcifunc);
	struct hwctx_disable_req ctx_req;

	/* Disable all pools */
	ctx_req.hdr.pcifunc = pcifunc;
	ctx_req.ctype = NPA_AQ_CTYPE_POOL;
	npa_lf_hwctx_disable(rvu, &ctx_req);

	/* Disable all auras */
	ctx_req.ctype = NPA_AQ_CTYPE_AURA;
	npa_lf_hwctx_disable(rvu, &ctx_req);

	npa_ctx_free(rvu, pfvf);
}