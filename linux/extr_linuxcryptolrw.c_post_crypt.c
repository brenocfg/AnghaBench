#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int offset; struct scatterlist* sg; } ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_5__ {TYPE_1__ virt; } ;
struct skcipher_walk {int nbytes; TYPE_3__ out; TYPE_2__ dst; } ;
struct skcipher_request {scalar_t__ cryptlen; } ;
struct scatterlist {unsigned int length; unsigned int offset; } ;
struct rctx {struct scatterlist* dst; struct scatterlist* dstbuf; scalar_t__ left; struct skcipher_request subreq; int /*<<< orphan*/ * buf; scalar_t__ ext; } ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int LRW_BLOCK_SIZE ; 
 int /*<<< orphan*/  be128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scatterwalk_crypto_chain (struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_done (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int post_crypt(struct skcipher_request *req)
{
	struct rctx *rctx = skcipher_request_ctx(req);
	be128 *buf = rctx->ext ?: rctx->buf;
	struct skcipher_request *subreq;
	const int bs = LRW_BLOCK_SIZE;
	struct skcipher_walk w;
	struct scatterlist *sg;
	unsigned offset;
	int err;

	subreq = &rctx->subreq;
	err = skcipher_walk_virt(&w, subreq, false);

	while (w.nbytes) {
		unsigned int avail = w.nbytes;
		be128 *wdst;

		wdst = w.dst.virt.addr;

		do {
			be128_xor(wdst, buf++, wdst);
			wdst++;
		} while ((avail -= bs) >= bs);

		err = skcipher_walk_done(&w, avail);
	}

	rctx->left -= subreq->cryptlen;

	if (err || !rctx->left)
		goto out;

	rctx->dst = rctx->dstbuf;

	scatterwalk_done(&w.out, 0, 1);
	sg = w.out.sg;
	offset = w.out.offset;

	if (rctx->dst != sg) {
		rctx->dst[0] = *sg;
		sg_unmark_end(rctx->dst);
		scatterwalk_crypto_chain(rctx->dst, sg_next(sg), 2);
	}
	rctx->dst[0].length -= offset - sg->offset;
	rctx->dst[0].offset = offset;

out:
	return err;
}