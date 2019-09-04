#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qce_sha_reqctx {unsigned long flags; int src_nents; int /*<<< orphan*/  result_sg; int /*<<< orphan*/  authklen; int /*<<< orphan*/  authkey; } ;
struct qce_sha_ctx {int /*<<< orphan*/  authkey; } ;
struct TYPE_4__ {int /*<<< orphan*/  result_buf; } ;
struct qce_device {int /*<<< orphan*/  dev; TYPE_1__ dma; } ;
struct qce_alg_template {int /*<<< orphan*/  crypto_alg_type; struct qce_device* qce; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
struct ahash_request {int /*<<< orphan*/ * src; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_KEYSIZE_128 ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IS_CMAC (unsigned long) ; 
 scalar_t__ IS_SHA_HMAC (unsigned long) ; 
 int /*<<< orphan*/  QCE_RESULT_BUF_SZ ; 
 int /*<<< orphan*/  QCE_SHA_HMAC_KEY_SIZE ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct qce_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct qce_sha_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qce_ahash_done ; 
 int /*<<< orphan*/  qce_dma_issue_pending (TYPE_1__*) ; 
 int qce_dma_prep_sgs (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct crypto_async_request*) ; 
 int /*<<< orphan*/  qce_dma_terminate_all (TYPE_1__*) ; 
 int qce_start (struct crypto_async_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sg_nents_for_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qce_alg_template* to_ahash_tmpl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qce_ahash_async_req_handle(struct crypto_async_request *async_req)
{
	struct ahash_request *req = ahash_request_cast(async_req);
	struct qce_sha_reqctx *rctx = ahash_request_ctx(req);
	struct qce_sha_ctx *ctx = crypto_tfm_ctx(async_req->tfm);
	struct qce_alg_template *tmpl = to_ahash_tmpl(async_req->tfm);
	struct qce_device *qce = tmpl->qce;
	unsigned long flags = rctx->flags;
	int ret;

	if (IS_SHA_HMAC(flags)) {
		rctx->authkey = ctx->authkey;
		rctx->authklen = QCE_SHA_HMAC_KEY_SIZE;
	} else if (IS_CMAC(flags)) {
		rctx->authkey = ctx->authkey;
		rctx->authklen = AES_KEYSIZE_128;
	}

	rctx->src_nents = sg_nents_for_len(req->src, req->nbytes);
	if (rctx->src_nents < 0) {
		dev_err(qce->dev, "Invalid numbers of src SG.\n");
		return rctx->src_nents;
	}

	ret = dma_map_sg(qce->dev, req->src, rctx->src_nents, DMA_TO_DEVICE);
	if (ret < 0)
		return ret;

	sg_init_one(&rctx->result_sg, qce->dma.result_buf, QCE_RESULT_BUF_SZ);

	ret = dma_map_sg(qce->dev, &rctx->result_sg, 1, DMA_FROM_DEVICE);
	if (ret < 0)
		goto error_unmap_src;

	ret = qce_dma_prep_sgs(&qce->dma, req->src, rctx->src_nents,
			       &rctx->result_sg, 1, qce_ahash_done, async_req);
	if (ret)
		goto error_unmap_dst;

	qce_dma_issue_pending(&qce->dma);

	ret = qce_start(async_req, tmpl->crypto_alg_type, 0, 0);
	if (ret)
		goto error_terminate;

	return 0;

error_terminate:
	qce_dma_terminate_all(&qce->dma);
error_unmap_dst:
	dma_unmap_sg(qce->dev, &rctx->result_sg, 1, DMA_FROM_DEVICE);
error_unmap_src:
	dma_unmap_sg(qce->dev, req->src, rctx->src_nents, DMA_TO_DEVICE);
	return ret;
}