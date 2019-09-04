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
typedef  int /*<<< orphan*/  u32 ;
struct sun4i_tfm_ctx {unsigned int keylen; int /*<<< orphan*/ * key; struct sun4i_ss_ctx* ss; } ;
struct sun4i_ss_ctx {int /*<<< orphan*/  slock; scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct sun4i_cipher_req_ctx {int /*<<< orphan*/  mode; } ;
struct skcipher_request {unsigned int cryptlen; scalar_t__ iv; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct sg_mapping_iter {unsigned int length; scalar_t__ addr; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_FROM_SG ; 
 int SG_MITER_TO_SG ; 
 scalar_t__ SS_CTL ; 
 scalar_t__ SS_FCSR ; 
 scalar_t__ SS_IV0 ; 
 scalar_t__ SS_KEY0 ; 
 scalar_t__ SS_RXFIFO ; 
 int /*<<< orphan*/  SS_RXFIFO_SPACES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_RX_DEFAULT ; 
 scalar_t__ SS_TXFIFO ; 
 int /*<<< orphan*/  SS_TXFIFO_SPACES (int /*<<< orphan*/ ) ; 
 struct sun4i_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 unsigned int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 unsigned int min3 (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  readsl (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 
 struct sun4i_cipher_req_ctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writesl (scalar_t__,scalar_t__,unsigned int) ; 

__attribute__((used)) static int sun4i_ss_opti_poll(struct skcipher_request *areq)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	struct sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	struct sun4i_ss_ctx *ss = op->ss;
	unsigned int ivsize = crypto_skcipher_ivsize(tfm);
	struct sun4i_cipher_req_ctx *ctx = skcipher_request_ctx(areq);
	u32 mode = ctx->mode;
	/* when activating SS, the default FIFO space is SS_RX_DEFAULT(32) */
	u32 rx_cnt = SS_RX_DEFAULT;
	u32 tx_cnt = 0;
	u32 spaces;
	u32 v;
	int err = 0;
	unsigned int i;
	unsigned int ileft = areq->cryptlen;
	unsigned int oleft = areq->cryptlen;
	unsigned int todo;
	struct sg_mapping_iter mi, mo;
	unsigned int oi, oo; /* offset for in and out */
	unsigned long flags;

	if (!areq->cryptlen)
		return 0;

	if (!areq->iv) {
		dev_err_ratelimited(ss->dev, "ERROR: Empty IV\n");
		return -EINVAL;
	}

	if (!areq->src || !areq->dst) {
		dev_err_ratelimited(ss->dev, "ERROR: Some SGs are NULL\n");
		return -EINVAL;
	}

	spin_lock_irqsave(&ss->slock, flags);

	for (i = 0; i < op->keylen; i += 4)
		writel(*(op->key + i / 4), ss->base + SS_KEY0 + i);

	if (areq->iv) {
		for (i = 0; i < 4 && i < ivsize / 4; i++) {
			v = *(u32 *)(areq->iv + i * 4);
			writel(v, ss->base + SS_IV0 + i * 4);
		}
	}
	writel(mode, ss->base + SS_CTL);

	sg_miter_start(&mi, areq->src, sg_nents(areq->src),
		       SG_MITER_FROM_SG | SG_MITER_ATOMIC);
	sg_miter_start(&mo, areq->dst, sg_nents(areq->dst),
		       SG_MITER_TO_SG | SG_MITER_ATOMIC);
	sg_miter_next(&mi);
	sg_miter_next(&mo);
	if (!mi.addr || !mo.addr) {
		dev_err_ratelimited(ss->dev, "ERROR: sg_miter return null\n");
		err = -EINVAL;
		goto release_ss;
	}

	ileft = areq->cryptlen / 4;
	oleft = areq->cryptlen / 4;
	oi = 0;
	oo = 0;
	do {
		todo = min3(rx_cnt, ileft, (mi.length - oi) / 4);
		if (todo) {
			ileft -= todo;
			writesl(ss->base + SS_RXFIFO, mi.addr + oi, todo);
			oi += todo * 4;
		}
		if (oi == mi.length) {
			sg_miter_next(&mi);
			oi = 0;
		}

		spaces = readl(ss->base + SS_FCSR);
		rx_cnt = SS_RXFIFO_SPACES(spaces);
		tx_cnt = SS_TXFIFO_SPACES(spaces);

		todo = min3(tx_cnt, oleft, (mo.length - oo) / 4);
		if (todo) {
			oleft -= todo;
			readsl(ss->base + SS_TXFIFO, mo.addr + oo, todo);
			oo += todo * 4;
		}
		if (oo == mo.length) {
			sg_miter_next(&mo);
			oo = 0;
		}
	} while (oleft);

	if (areq->iv) {
		for (i = 0; i < 4 && i < ivsize / 4; i++) {
			v = readl(ss->base + SS_IV0 + i * 4);
			*(u32 *)(areq->iv + i * 4) = v;
		}
	}

release_ss:
	sg_miter_stop(&mi);
	sg_miter_stop(&mo);
	writel(0, ss->base + SS_CTL);
	spin_unlock_irqrestore(&ss->slock, flags);
	return err;
}