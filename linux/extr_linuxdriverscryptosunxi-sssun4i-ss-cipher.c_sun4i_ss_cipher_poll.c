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
typedef  int u32 ;
struct sun4i_tfm_ctx {unsigned int keylen; int* key; struct sun4i_ss_ctx* ss; } ;
struct sun4i_ss_ctx {int /*<<< orphan*/  slock; scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct sun4i_cipher_req_ctx {int mode; } ;
struct skcipher_request {unsigned int cryptlen; scalar_t__ iv; struct scatterlist* dst; struct scatterlist* src; } ;
struct sg_mapping_iter {char* addr; unsigned int length; } ;
struct scatterlist {int length; } ;
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
 int SS_RXFIFO_SPACES (int) ; 
 int SS_RX_DEFAULT ; 
 int SS_RX_MAX ; 
 scalar_t__ SS_TXFIFO ; 
 int SS_TXFIFO_SPACES (int) ; 
 int SS_TX_MAX ; 
 struct sun4i_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 unsigned int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int,unsigned int,unsigned int,unsigned int,int,unsigned int,unsigned int,unsigned int,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int min3 (int,unsigned int,unsigned int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  readsl (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_nents (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 struct sun4i_cipher_req_ctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sun4i_ss_opti_poll (struct skcipher_request*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writesl (scalar_t__,char*,unsigned int) ; 

__attribute__((used)) static int sun4i_ss_cipher_poll(struct skcipher_request *areq)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	struct sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	struct sun4i_ss_ctx *ss = op->ss;
	int no_chunk = 1;
	struct scatterlist *in_sg = areq->src;
	struct scatterlist *out_sg = areq->dst;
	unsigned int ivsize = crypto_skcipher_ivsize(tfm);
	struct sun4i_cipher_req_ctx *ctx = skcipher_request_ctx(areq);
	u32 mode = ctx->mode;
	/* when activating SS, the default FIFO space is SS_RX_DEFAULT(32) */
	u32 rx_cnt = SS_RX_DEFAULT;
	u32 tx_cnt = 0;
	u32 v;
	u32 spaces;
	int err = 0;
	unsigned int i;
	unsigned int ileft = areq->cryptlen;
	unsigned int oleft = areq->cryptlen;
	unsigned int todo;
	struct sg_mapping_iter mi, mo;
	unsigned int oi, oo;	/* offset for in and out */
	char buf[4 * SS_RX_MAX];/* buffer for linearize SG src */
	char bufo[4 * SS_TX_MAX]; /* buffer for linearize SG dst */
	unsigned int ob = 0;	/* offset in buf */
	unsigned int obo = 0;	/* offset in bufo*/
	unsigned int obl = 0;	/* length of data in bufo */
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

	/*
	 * if we have only SGs with size multiple of 4,
	 * we can use the SS optimized function
	 */
	while (in_sg && no_chunk == 1) {
		if (in_sg->length % 4)
			no_chunk = 0;
		in_sg = sg_next(in_sg);
	}
	while (out_sg && no_chunk == 1) {
		if (out_sg->length % 4)
			no_chunk = 0;
		out_sg = sg_next(out_sg);
	}

	if (no_chunk == 1)
		return sun4i_ss_opti_poll(areq);

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
	ileft = areq->cryptlen;
	oleft = areq->cryptlen;
	oi = 0;
	oo = 0;

	while (oleft) {
		if (ileft) {
			/*
			 * todo is the number of consecutive 4byte word that we
			 * can read from current SG
			 */
			todo = min3(rx_cnt, ileft / 4, (mi.length - oi) / 4);
			if (todo && !ob) {
				writesl(ss->base + SS_RXFIFO, mi.addr + oi,
					todo);
				ileft -= todo * 4;
				oi += todo * 4;
			} else {
				/*
				 * not enough consecutive bytes, so we need to
				 * linearize in buf. todo is in bytes
				 * After that copy, if we have a multiple of 4
				 * we need to be able to write all buf in one
				 * pass, so it is why we min() with rx_cnt
				 */
				todo = min3(rx_cnt * 4 - ob, ileft,
					    mi.length - oi);
				memcpy(buf + ob, mi.addr + oi, todo);
				ileft -= todo;
				oi += todo;
				ob += todo;
				if (!(ob % 4)) {
					writesl(ss->base + SS_RXFIFO, buf,
						ob / 4);
					ob = 0;
				}
			}
			if (oi == mi.length) {
				sg_miter_next(&mi);
				oi = 0;
			}
		}

		spaces = readl(ss->base + SS_FCSR);
		rx_cnt = SS_RXFIFO_SPACES(spaces);
		tx_cnt = SS_TXFIFO_SPACES(spaces);
		dev_dbg(ss->dev, "%x %u/%u %u/%u cnt=%u %u/%u %u/%u cnt=%u %u\n",
			mode,
			oi, mi.length, ileft, areq->cryptlen, rx_cnt,
			oo, mo.length, oleft, areq->cryptlen, tx_cnt, ob);

		if (!tx_cnt)
			continue;
		/* todo in 4bytes word */
		todo = min3(tx_cnt, oleft / 4, (mo.length - oo) / 4);
		if (todo) {
			readsl(ss->base + SS_TXFIFO, mo.addr + oo, todo);
			oleft -= todo * 4;
			oo += todo * 4;
			if (oo == mo.length) {
				sg_miter_next(&mo);
				oo = 0;
			}
		} else {
			/*
			 * read obl bytes in bufo, we read at maximum for
			 * emptying the device
			 */
			readsl(ss->base + SS_TXFIFO, bufo, tx_cnt);
			obl = tx_cnt * 4;
			obo = 0;
			do {
				/*
				 * how many bytes we can copy ?
				 * no more than remaining SG size
				 * no more than remaining buffer
				 * no need to test against oleft
				 */
				todo = min(mo.length - oo, obl - obo);
				memcpy(mo.addr + oo, bufo + obo, todo);
				oleft -= todo;
				obo += todo;
				oo += todo;
				if (oo == mo.length) {
					sg_miter_next(&mo);
					oo = 0;
				}
			} while (obo < obl);
			/* bufo must be fully used here */
		}
	}
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