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
struct sahara_sha_reqctx {unsigned int buf_cnt; unsigned int total; scalar_t__ in_sg; int /*<<< orphan*/  rembuf; scalar_t__ in_sg_chain; scalar_t__ buf; scalar_t__ last; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {unsigned int nbytes; scalar_t__ src; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 struct sahara_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sahara_walk_and_recalc (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__,scalar_t__,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_chain (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  sg_init_one (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_table (scalar_t__,int) ; 
 int /*<<< orphan*/  sg_set_buf (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sahara_sha_prepare_request(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct sahara_sha_reqctx *rctx = ahash_request_ctx(req);
	unsigned int hash_later;
	unsigned int block_size;
	unsigned int len;

	block_size = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	/* append bytes from previous operation */
	len = rctx->buf_cnt + req->nbytes;

	/* only the last transfer can be padded in hardware */
	if (!rctx->last && (len < block_size)) {
		/* to few data, save for next operation */
		scatterwalk_map_and_copy(rctx->buf + rctx->buf_cnt, req->src,
					 0, req->nbytes, 0);
		rctx->buf_cnt += req->nbytes;

		return 0;
	}

	/* add data from previous operation first */
	if (rctx->buf_cnt)
		memcpy(rctx->rembuf, rctx->buf, rctx->buf_cnt);

	/* data must always be a multiple of block_size */
	hash_later = rctx->last ? 0 : len & (block_size - 1);
	if (hash_later) {
		unsigned int offset = req->nbytes - hash_later;
		/* Save remaining bytes for later use */
		scatterwalk_map_and_copy(rctx->buf, req->src, offset,
					hash_later, 0);
	}

	/* nbytes should now be multiple of blocksize */
	req->nbytes = req->nbytes - hash_later;

	sahara_walk_and_recalc(req->src, req->nbytes);

	/* have data from previous operation and current */
	if (rctx->buf_cnt && req->nbytes) {
		sg_init_table(rctx->in_sg_chain, 2);
		sg_set_buf(rctx->in_sg_chain, rctx->rembuf, rctx->buf_cnt);

		sg_chain(rctx->in_sg_chain, 2, req->src);

		rctx->total = req->nbytes + rctx->buf_cnt;
		rctx->in_sg = rctx->in_sg_chain;

		req->src = rctx->in_sg_chain;
	/* only data from previous operation */
	} else if (rctx->buf_cnt) {
		if (req->src)
			rctx->in_sg = req->src;
		else
			rctx->in_sg = rctx->in_sg_chain;
		/* buf was copied into rembuf above */
		sg_init_one(rctx->in_sg, rctx->rembuf, rctx->buf_cnt);
		rctx->total = rctx->buf_cnt;
	/* no data from previous operation */
	} else {
		rctx->in_sg = req->src;
		rctx->total = req->nbytes;
		req->src = rctx->in_sg;
	}

	/* on next call, we only have the remaining data in the buffer */
	rctx->buf_cnt = hash_later;

	return -EINPROGRESS;
}