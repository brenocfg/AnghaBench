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
struct s5p_mfc_regs {scalar_t__ instance_id; scalar_t__ e_tmv_buffer1; scalar_t__ e_tmv_buffer0; scalar_t__ e_scratch_buffer_size; scalar_t__ e_scratch_buffer_addr; scalar_t__ e_me_buffer; scalar_t__ e_chroma_dpb; scalar_t__ e_luma_dpb; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_cmds; struct s5p_mfc_regs* mfc_regs; } ;
struct TYPE_2__ {size_t dma; int size; } ;
struct s5p_mfc_ctx {int pb_count; size_t scratch_buf_size; int tmv_buffer_size; size_t inst_no; scalar_t__ me_buffer_size; scalar_t__ chroma_dpb_size; scalar_t__ luma_dpb_size; TYPE_1__ bank1; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_MFCV10 (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  S5P_FIMV_CH_INIT_BUFS_V6 ; 
 int /*<<< orphan*/  cmd_host2risc ; 
 int /*<<< orphan*/  mfc_debug (int,char*,...) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static int s5p_mfc_set_enc_ref_buffer_v6(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	size_t buf_addr1;
	int i, buf_size1;

	mfc_debug_enter();

	buf_addr1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;

	mfc_debug(2, "Buf1: %p (%d)\n", (void *)buf_addr1, buf_size1);

	if (IS_MFCV10(dev)) {
		/* start address of per buffer is aligned */
		for (i = 0; i < ctx->pb_count; i++) {
			writel(buf_addr1, mfc_regs->e_luma_dpb + (4 * i));
			buf_addr1 += ctx->luma_dpb_size;
			buf_size1 -= ctx->luma_dpb_size;
		}
		for (i = 0; i < ctx->pb_count; i++) {
			writel(buf_addr1, mfc_regs->e_chroma_dpb + (4 * i));
			buf_addr1 += ctx->chroma_dpb_size;
			buf_size1 -= ctx->chroma_dpb_size;
		}
		for (i = 0; i < ctx->pb_count; i++) {
			writel(buf_addr1, mfc_regs->e_me_buffer + (4 * i));
			buf_addr1 += ctx->me_buffer_size;
			buf_size1 -= ctx->me_buffer_size;
		}
	} else {
		for (i = 0; i < ctx->pb_count; i++) {
			writel(buf_addr1, mfc_regs->e_luma_dpb + (4 * i));
			buf_addr1 += ctx->luma_dpb_size;
			writel(buf_addr1, mfc_regs->e_chroma_dpb + (4 * i));
			buf_addr1 += ctx->chroma_dpb_size;
			writel(buf_addr1, mfc_regs->e_me_buffer + (4 * i));
			buf_addr1 += ctx->me_buffer_size;
			buf_size1 -= (ctx->luma_dpb_size + ctx->chroma_dpb_size
					+ ctx->me_buffer_size);
		}
	}

	writel(buf_addr1, mfc_regs->e_scratch_buffer_addr);
	writel(ctx->scratch_buf_size, mfc_regs->e_scratch_buffer_size);
	buf_addr1 += ctx->scratch_buf_size;
	buf_size1 -= ctx->scratch_buf_size;

	writel(buf_addr1, mfc_regs->e_tmv_buffer0);
	buf_addr1 += ctx->tmv_buffer_size >> 1;
	writel(buf_addr1, mfc_regs->e_tmv_buffer1);
	buf_addr1 += ctx->tmv_buffer_size >> 1;
	buf_size1 -= ctx->tmv_buffer_size;

	mfc_debug(2, "Buf1: %zu, buf_size1: %d (ref frames %d)\n",
			buf_addr1, buf_size1, ctx->pb_count);
	if (buf_size1 < 0) {
		mfc_debug(2, "Not enough memory has been allocated.\n");
		return -ENOMEM;
	}

	writel(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
			S5P_FIMV_CH_INIT_BUFS_V6, NULL);

	mfc_debug_leave();

	return 0;
}