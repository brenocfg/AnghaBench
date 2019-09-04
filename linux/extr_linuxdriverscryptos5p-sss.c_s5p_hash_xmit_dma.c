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
struct s5p_hash_reqctx {int error; size_t digcnt; size_t total; int /*<<< orphan*/  sg; int /*<<< orphan*/  sg_len; } ;
struct s5p_aes_dev {unsigned int hash_sg_cnt; int /*<<< orphan*/  hash_sg_iter; int /*<<< orphan*/  hash_flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  hash_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  HASH_FLAGS_DMA_ACTIVE ; 
 int /*<<< orphan*/  HASH_FLAGS_FINAL ; 
 struct s5p_hash_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_hash_write_ctrl (struct s5p_aes_dev*,size_t,int) ; 
 int /*<<< orphan*/  s5p_set_dma_hashdata (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5p_hash_xmit_dma(struct s5p_aes_dev *dd, size_t length,
			     bool final)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(dd->hash_req);
	unsigned int cnt;

	cnt = dma_map_sg(dd->dev, ctx->sg, ctx->sg_len, DMA_TO_DEVICE);
	if (!cnt) {
		dev_err(dd->dev, "dma_map_sg error\n");
		ctx->error = true;
		return -EINVAL;
	}

	set_bit(HASH_FLAGS_DMA_ACTIVE, &dd->hash_flags);
	dd->hash_sg_iter = ctx->sg;
	dd->hash_sg_cnt = cnt;
	s5p_hash_write_ctrl(dd, length, final);
	ctx->digcnt += length;
	ctx->total -= length;

	/* catch last interrupt */
	if (final)
		set_bit(HASH_FLAGS_FINAL, &dd->hash_flags);

	s5p_set_dma_hashdata(dd, dd->hash_sg_iter); /* DMA starts */

	return -EINPROGRESS;
}