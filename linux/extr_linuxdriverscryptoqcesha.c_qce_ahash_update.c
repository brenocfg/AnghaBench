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
struct scatterlist {int dummy; } ;
struct qce_sha_reqctx {unsigned int count; unsigned int buflen; unsigned int nbytes_orig; struct scatterlist* sg; int /*<<< orphan*/  tmpbuf; scalar_t__ buf; struct scatterlist* src_orig; } ;
struct qce_device {int (* async_req_enqueue ) (struct qce_device*,TYPE_1__*) ;} ;
struct qce_alg_template {struct qce_device* qce; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {unsigned int nbytes; TYPE_1__ base; struct scatterlist* src; } ;

/* Variables and functions */
 int EINVAL ; 
 struct qce_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__,struct scatterlist*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_chain (struct scatterlist*,int,struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct qce_device*,TYPE_1__*) ; 
 struct qce_alg_template* to_ahash_tmpl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qce_ahash_update(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct qce_sha_reqctx *rctx = ahash_request_ctx(req);
	struct qce_alg_template *tmpl = to_ahash_tmpl(req->base.tfm);
	struct qce_device *qce = tmpl->qce;
	struct scatterlist *sg_last, *sg;
	unsigned int total, len;
	unsigned int hash_later;
	unsigned int nbytes;
	unsigned int blocksize;

	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	rctx->count += req->nbytes;

	/* check for buffer from previous updates and append it */
	total = req->nbytes + rctx->buflen;

	if (total <= blocksize) {
		scatterwalk_map_and_copy(rctx->buf + rctx->buflen, req->src,
					 0, req->nbytes, 0);
		rctx->buflen += req->nbytes;
		return 0;
	}

	/* save the original req structure fields */
	rctx->src_orig = req->src;
	rctx->nbytes_orig = req->nbytes;

	/*
	 * if we have data from previous update copy them on buffer. The old
	 * data will be combined with current request bytes.
	 */
	if (rctx->buflen)
		memcpy(rctx->tmpbuf, rctx->buf, rctx->buflen);

	/* calculate how many bytes will be hashed later */
	hash_later = total % blocksize;
	if (hash_later) {
		unsigned int src_offset = req->nbytes - hash_later;
		scatterwalk_map_and_copy(rctx->buf, req->src, src_offset,
					 hash_later, 0);
	}

	/* here nbytes is multiple of blocksize */
	nbytes = total - hash_later;

	len = rctx->buflen;
	sg = sg_last = req->src;

	while (len < nbytes && sg) {
		if (len + sg_dma_len(sg) > nbytes)
			break;
		len += sg_dma_len(sg);
		sg_last = sg;
		sg = sg_next(sg);
	}

	if (!sg_last)
		return -EINVAL;

	sg_mark_end(sg_last);

	if (rctx->buflen) {
		sg_init_table(rctx->sg, 2);
		sg_set_buf(rctx->sg, rctx->tmpbuf, rctx->buflen);
		sg_chain(rctx->sg, 2, req->src);
		req->src = rctx->sg;
	}

	req->nbytes = nbytes;
	rctx->buflen = hash_later;

	return qce->async_req_enqueue(tmpl->qce, &req->base);
}