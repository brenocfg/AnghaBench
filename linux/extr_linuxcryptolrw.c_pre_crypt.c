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
struct TYPE_10__ {unsigned int offset; struct scatterlist* sg; } ;
struct TYPE_8__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_9__ {TYPE_3__ virt; } ;
struct TYPE_6__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_7__ {TYPE_1__ virt; } ;
struct skcipher_walk {int nbytes; TYPE_5__ in; TYPE_4__ dst; TYPE_2__ src; int /*<<< orphan*/ * iv; } ;
struct skcipher_request {unsigned int cryptlen; int /*<<< orphan*/ * iv; } ;
struct scatterlist {unsigned int length; unsigned int offset; } ;
struct rctx {unsigned int left; struct scatterlist* src; struct scatterlist* srcbuf; struct scatterlist* dst; int /*<<< orphan*/  t; struct skcipher_request subreq; int /*<<< orphan*/ * buf; scalar_t__ ext; } ;
struct priv {struct crypto_skcipher* child; int /*<<< orphan*/ * mulinc; } ;
struct crypto_skcipher {int dummy; } ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int LRW_BLOCK_SIZE ; 
 int /*<<< orphan*/  be128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct priv* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 size_t get_index128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scatterwalk_crypto_chain (struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_done (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,struct crypto_skcipher*) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int pre_crypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct rctx *rctx = skcipher_request_ctx(req);
	struct priv *ctx = crypto_skcipher_ctx(tfm);
	be128 *buf = rctx->ext ?: rctx->buf;
	struct skcipher_request *subreq;
	const int bs = LRW_BLOCK_SIZE;
	struct skcipher_walk w;
	struct scatterlist *sg;
	unsigned cryptlen;
	unsigned offset;
	be128 *iv;
	bool more;
	int err;

	subreq = &rctx->subreq;
	skcipher_request_set_tfm(subreq, tfm);

	cryptlen = subreq->cryptlen;
	more = rctx->left > cryptlen;
	if (!more)
		cryptlen = rctx->left;

	skcipher_request_set_crypt(subreq, rctx->src, rctx->dst,
				   cryptlen, req->iv);

	err = skcipher_walk_virt(&w, subreq, false);
	iv = w.iv;

	while (w.nbytes) {
		unsigned int avail = w.nbytes;
		be128 *wsrc;
		be128 *wdst;

		wsrc = w.src.virt.addr;
		wdst = w.dst.virt.addr;

		do {
			*buf++ = rctx->t;
			be128_xor(wdst++, &rctx->t, wsrc++);

			/* T <- I*Key2, using the optimization
			 * discussed in the specification */
			be128_xor(&rctx->t, &rctx->t,
				  &ctx->mulinc[get_index128(iv)]);
			inc(iv);
		} while ((avail -= bs) >= bs);

		err = skcipher_walk_done(&w, avail);
	}

	skcipher_request_set_tfm(subreq, ctx->child);
	skcipher_request_set_crypt(subreq, rctx->dst, rctx->dst,
				   cryptlen, NULL);

	if (err || !more)
		goto out;

	rctx->src = rctx->srcbuf;

	scatterwalk_done(&w.in, 0, 1);
	sg = w.in.sg;
	offset = w.in.offset;

	if (rctx->src != sg) {
		rctx->src[0] = *sg;
		sg_unmark_end(rctx->src);
		scatterwalk_crypto_chain(rctx->src, sg_next(sg), 2);
	}
	rctx->src[0].length -= offset - sg->offset;
	rctx->src[0].offset = offset;

out:
	return err;
}