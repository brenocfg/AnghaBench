#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_7__ {unsigned int width; unsigned int height; TYPE_2__* plane_fmt; } ;
struct jpu_q_data {TYPE_4__* fmtinfo; TYPE_3__ format; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct jpu_ctx {struct jpu* jpu; int /*<<< orphan*/  compr_quality; scalar_t__ encoder; struct jpu_q_data cap_q; struct jpu_q_data out_q; TYPE_1__ fh; } ;
struct jpu_buffer {unsigned char subsampling; int /*<<< orphan*/  compr_quality; } ;
struct jpu {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; struct jpu_ctx* curr; } ;
struct TYPE_8__ {unsigned char num_planes; unsigned char subsampling; } ;
struct TYPE_6__ {unsigned int bytesperline; } ;

/* Variables and functions */
 int /*<<< orphan*/  JCCMD ; 
 unsigned int JCCMD_JSRT ; 
 int /*<<< orphan*/  JCHSZD ; 
 int /*<<< orphan*/  JCHSZU ; 
 int /*<<< orphan*/  JCHTN ; 
 int JCHTN_AC_SHIFT (int) ; 
 int JCHTN_DC_SHIFT (int) ; 
 int /*<<< orphan*/  JCMOD ; 
 unsigned int JCMOD_DSP_DEC ; 
 unsigned int JCMOD_DSP_ENC ; 
 unsigned int JCMOD_MSKIP_ENABLE ; 
 unsigned int JCMOD_PCTR ; 
 unsigned int JCMOD_REDU_420 ; 
 unsigned int JCMOD_REDU_422 ; 
 int /*<<< orphan*/  JCQTN ; 
 int JCQTN_SHIFT (int) ; 
 unsigned int JCSZ_MASK ; 
 int /*<<< orphan*/  JCVSZD ; 
 int /*<<< orphan*/  JCVSZU ; 
 int /*<<< orphan*/  JIFDCNT ; 
 unsigned int JIFDCNT_SWAP_WB ; 
 int /*<<< orphan*/  JIFDDCA1 ; 
 int /*<<< orphan*/  JIFDDMW ; 
 int /*<<< orphan*/  JIFDDYA1 ; 
 int /*<<< orphan*/  JIFDSA1 ; 
 int /*<<< orphan*/  JIFECNT ; 
 unsigned int JIFECNT_INFT_420 ; 
 unsigned int JIFECNT_INFT_422 ; 
 unsigned int JIFECNT_SWAP_WB ; 
 int /*<<< orphan*/  JIFEDA1 ; 
 int /*<<< orphan*/  JIFESCA1 ; 
 int /*<<< orphan*/  JIFESHSZ ; 
 int /*<<< orphan*/  JIFESMW ; 
 int /*<<< orphan*/  JIFESVSZ ; 
 int /*<<< orphan*/  JIFESYA1 ; 
 int /*<<< orphan*/  JINTE ; 
 unsigned int JINTE_ERR ; 
 unsigned int JINTE_TRANSF_COMPL ; 
 unsigned char JPU_JPEG_420 ; 
 unsigned long JPU_JPEG_HDR_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jpu_cleanup (struct jpu_ctx*,int) ; 
 int /*<<< orphan*/  jpu_set_htbl (struct jpu*) ; 
 int /*<<< orphan*/  jpu_set_qtbl (struct jpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ jpu_wait_reset (struct jpu*) ; 
 int /*<<< orphan*/  jpu_write (struct jpu*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 unsigned long vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int) ; 
 struct jpu_buffer* vb2_to_jpu_buffer (struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static void jpu_device_run(void *priv)
{
	struct jpu_ctx *ctx = priv;
	struct jpu *jpu = ctx->jpu;
	struct jpu_buffer *jpu_buf;
	struct jpu_q_data *q_data;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	unsigned int w, h, bpl;
	unsigned char num_planes, subsampling;
	unsigned long flags;

	/* ...wait until module reset completes; we have mutex locked here */
	if (jpu_wait_reset(jpu)) {
		jpu_cleanup(ctx, true);
		return;
	}

	spin_lock_irqsave(&ctx->jpu->lock, flags);

	jpu->curr = ctx;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	if (ctx->encoder) {
		jpu_buf = vb2_to_jpu_buffer(dst_buf);
		q_data = &ctx->out_q;
	} else {
		jpu_buf = vb2_to_jpu_buffer(src_buf);
		q_data = &ctx->cap_q;
	}

	w = q_data->format.width;
	h = q_data->format.height;
	bpl = q_data->format.plane_fmt[0].bytesperline;
	num_planes = q_data->fmtinfo->num_planes;
	subsampling = q_data->fmtinfo->subsampling;

	if (ctx->encoder) {
		unsigned long src_1_addr, src_2_addr, dst_addr;
		unsigned int redu, inft;

		dst_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
		src_1_addr =
			vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
		if (num_planes > 1)
			src_2_addr = vb2_dma_contig_plane_dma_addr(
					&src_buf->vb2_buf, 1);
		else
			src_2_addr = src_1_addr + w * h;

		jpu_buf->compr_quality = ctx->compr_quality;

		if (subsampling == JPU_JPEG_420) {
			redu = JCMOD_REDU_420;
			inft = JIFECNT_INFT_420;
		} else {
			redu = JCMOD_REDU_422;
			inft = JIFECNT_INFT_422;
		}

		/* only no marker mode works for encoding */
		jpu_write(jpu, JCMOD_DSP_ENC | JCMOD_PCTR | redu |
			  JCMOD_MSKIP_ENABLE, JCMOD);

		jpu_write(jpu, JIFECNT_SWAP_WB | inft, JIFECNT);
		jpu_write(jpu, JIFDCNT_SWAP_WB, JIFDCNT);
		jpu_write(jpu, JINTE_TRANSF_COMPL, JINTE);

		/* Y and C components source addresses */
		jpu_write(jpu, src_1_addr, JIFESYA1);
		jpu_write(jpu, src_2_addr, JIFESCA1);

		/* memory width */
		jpu_write(jpu, bpl, JIFESMW);

		jpu_write(jpu, (w >> 8) & JCSZ_MASK, JCHSZU);
		jpu_write(jpu, w & JCSZ_MASK, JCHSZD);

		jpu_write(jpu, (h >> 8) & JCSZ_MASK, JCVSZU);
		jpu_write(jpu, h & JCSZ_MASK, JCVSZD);

		jpu_write(jpu, w, JIFESHSZ);
		jpu_write(jpu, h, JIFESVSZ);

		jpu_write(jpu, dst_addr + JPU_JPEG_HDR_SIZE, JIFEDA1);

		jpu_write(jpu, 0 << JCQTN_SHIFT(1) | 1 << JCQTN_SHIFT(2) |
			  1 << JCQTN_SHIFT(3), JCQTN);

		jpu_write(jpu, 0 << JCHTN_AC_SHIFT(1) | 0 << JCHTN_DC_SHIFT(1) |
			  1 << JCHTN_AC_SHIFT(2) | 1 << JCHTN_DC_SHIFT(2) |
			  1 << JCHTN_AC_SHIFT(3) | 1 << JCHTN_DC_SHIFT(3),
			  JCHTN);

		jpu_set_qtbl(jpu, ctx->compr_quality);
		jpu_set_htbl(jpu);
	} else {
		unsigned long src_addr, dst_1_addr, dst_2_addr;

		if (jpu_buf->subsampling != subsampling) {
			dev_err(ctx->jpu->dev,
				"src and dst formats do not match.\n");
			spin_unlock_irqrestore(&ctx->jpu->lock, flags);
			jpu_cleanup(ctx, false);
			return;
		}

		src_addr = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
		dst_1_addr =
			vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
		if (q_data->fmtinfo->num_planes > 1)
			dst_2_addr = vb2_dma_contig_plane_dma_addr(
					&dst_buf->vb2_buf, 1);
		else
			dst_2_addr = dst_1_addr + w * h;

		/* ...set up decoder operation */
		jpu_write(jpu, JCMOD_DSP_DEC | JCMOD_PCTR, JCMOD);
		jpu_write(jpu, JIFECNT_SWAP_WB, JIFECNT);
		jpu_write(jpu, JIFDCNT_SWAP_WB, JIFDCNT);

		/* ...enable interrupts on transfer completion and d-g error */
		jpu_write(jpu, JINTE_TRANSF_COMPL | JINTE_ERR, JINTE);

		/* ...set source/destination addresses of encoded data */
		jpu_write(jpu, src_addr, JIFDSA1);
		jpu_write(jpu, dst_1_addr, JIFDDYA1);
		jpu_write(jpu, dst_2_addr, JIFDDCA1);

		jpu_write(jpu, bpl, JIFDDMW);
	}

	/* ...start encoder/decoder operation */
	jpu_write(jpu, JCCMD_JSRT, JCCMD);

	spin_unlock_irqrestore(&ctx->jpu->lock, flags);
}