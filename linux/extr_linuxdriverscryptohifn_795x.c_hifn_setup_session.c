#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {unsigned long offset; int /*<<< orphan*/  length; } ;
struct TYPE_7__ {int flags; } ;
struct hifn_request_context {scalar_t__ mode; int /*<<< orphan*/  type; int /*<<< orphan*/  op; int /*<<< orphan*/  ivsize; scalar_t__ iv; TYPE_3__ walk; } ;
struct hifn_device {scalar_t__ started; TYPE_2__* pdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  active; int /*<<< orphan*/  snum; } ;
struct hifn_context {int /*<<< orphan*/  keysize; int /*<<< orphan*/  key; struct hifn_device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {unsigned int nbytes; struct scatterlist* dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ACRYPTO_MODE_ECB ; 
 int ASYNC_FLAGS_MISALIGNED ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HIFN_DEFAULT_ACTIVE_NUM ; 
 int /*<<< orphan*/  HIFN_D_DST_DALIGN ; 
 scalar_t__ HIFN_QUEUE_LENGTH ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 struct hifn_request_context* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 struct hifn_context* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hifn_cipher_walk (struct ablkcipher_request*,TYPE_3__*) ; 
 int hifn_cipher_walk_init (TYPE_3__*,unsigned int,int /*<<< orphan*/ ) ; 
 int hifn_setup_dma (struct hifn_device*,struct hifn_context*,struct hifn_request_context*,int /*<<< orphan*/ ,struct scatterlist*,unsigned int,struct ablkcipher_request*) ; 
 unsigned long min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hifn_setup_session(struct ablkcipher_request *req)
{
	struct hifn_context *ctx = crypto_tfm_ctx(req->base.tfm);
	struct hifn_request_context *rctx = ablkcipher_request_ctx(req);
	struct hifn_device *dev = ctx->dev;
	unsigned long dlen, flags;
	unsigned int nbytes = req->nbytes, idx = 0;
	int err = -EINVAL, sg_num;
	struct scatterlist *dst;

	if (rctx->iv && !rctx->ivsize && rctx->mode != ACRYPTO_MODE_ECB)
		goto err_out_exit;

	rctx->walk.flags = 0;

	while (nbytes) {
		dst = &req->dst[idx];
		dlen = min(dst->length, nbytes);

		if (!IS_ALIGNED(dst->offset, HIFN_D_DST_DALIGN) ||
		    !IS_ALIGNED(dlen, HIFN_D_DST_DALIGN))
			rctx->walk.flags |= ASYNC_FLAGS_MISALIGNED;

		nbytes -= dlen;
		idx++;
	}

	if (rctx->walk.flags & ASYNC_FLAGS_MISALIGNED) {
		err = hifn_cipher_walk_init(&rctx->walk, idx, GFP_ATOMIC);
		if (err < 0)
			return err;
	}

	sg_num = hifn_cipher_walk(req, &rctx->walk);
	if (sg_num < 0) {
		err = sg_num;
		goto err_out_exit;
	}

	spin_lock_irqsave(&dev->lock, flags);
	if (dev->started + sg_num > HIFN_QUEUE_LENGTH) {
		err = -EAGAIN;
		goto err_out;
	}

	err = hifn_setup_dma(dev, ctx, rctx, req->src, req->dst, req->nbytes, req);
	if (err)
		goto err_out;

	dev->snum++;

	dev->active = HIFN_DEFAULT_ACTIVE_NUM;
	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;

err_out:
	spin_unlock_irqrestore(&dev->lock, flags);
err_out_exit:
	if (err) {
		dev_info(&dev->pdev->dev, "iv: %p [%d], key: %p [%d], mode: %u, op: %u, "
			 "type: %u, err: %d.\n",
			 rctx->iv, rctx->ivsize,
			 ctx->key, ctx->keysize,
			 rctx->mode, rctx->op, rctx->type, err);
	}

	return err;
}