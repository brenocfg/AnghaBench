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
typedef  unsigned int u32 ;
struct TYPE_6__ {unsigned int width; unsigned int height; } ;
struct coda_q_data {TYPE_1__ rect; } ;
struct coda_dev {TYPE_3__* devtype; } ;
struct coda_ctx {scalar_t__ tiled_map_type; int num_internal_frames; TYPE_4__* codec; TYPE_2__* internal_frames; struct coda_dev* dev; } ;
struct TYPE_10__ {unsigned int paddr; } ;
struct TYPE_9__ {scalar_t__ src_fourcc; scalar_t__ dst_fourcc; } ;
struct TYPE_8__ {scalar_t__ product; } ;
struct TYPE_7__ {TYPE_5__ buf; } ;

/* Variables and functions */
 scalar_t__ CODA_DX6 ; 
 int ENOMEM ; 
 scalar_t__ GDI_TILED_FRAME_MB_RASTER_MAP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 scalar_t__ V4L2_PIX_FMT_MPEG4 ; 
 int coda_alloc_context_buf (struct coda_ctx*,TYPE_5__*,size_t,char*) ; 
 int /*<<< orphan*/  coda_free_framebuffers (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_parabuf_write (struct coda_ctx*,int,unsigned int) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 unsigned int round_up (unsigned int,int) ; 

__attribute__((used)) static int coda_alloc_framebuffers(struct coda_ctx *ctx,
				   struct coda_q_data *q_data, u32 fourcc)
{
	struct coda_dev *dev = ctx->dev;
	unsigned int ysize, ycbcr_size;
	int ret;
	int i;

	if (ctx->codec->src_fourcc == V4L2_PIX_FMT_H264 ||
	    ctx->codec->dst_fourcc == V4L2_PIX_FMT_H264 ||
	    ctx->codec->src_fourcc == V4L2_PIX_FMT_MPEG4 ||
	    ctx->codec->dst_fourcc == V4L2_PIX_FMT_MPEG4)
		ysize = round_up(q_data->rect.width, 16) *
			round_up(q_data->rect.height, 16);
	else
		ysize = round_up(q_data->rect.width, 8) * q_data->rect.height;

	if (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP)
		ycbcr_size = round_up(ysize, 4096) + ysize / 2;
	else
		ycbcr_size = ysize + ysize / 2;

	/* Allocate frame buffers */
	for (i = 0; i < ctx->num_internal_frames; i++) {
		size_t size = ycbcr_size;
		char *name;

		/* Add space for mvcol buffers */
		if (dev->devtype->product != CODA_DX6 &&
		    (ctx->codec->src_fourcc == V4L2_PIX_FMT_H264 ||
		     (ctx->codec->src_fourcc == V4L2_PIX_FMT_MPEG4 && i == 0)))
			size += ysize / 4;
		name = kasprintf(GFP_KERNEL, "fb%d", i);
		if (!name) {
			coda_free_framebuffers(ctx);
			return -ENOMEM;
		}
		ret = coda_alloc_context_buf(ctx, &ctx->internal_frames[i].buf,
					     size, name);
		kfree(name);
		if (ret < 0) {
			coda_free_framebuffers(ctx);
			return ret;
		}
	}

	/* Register frame buffers in the parameter buffer */
	for (i = 0; i < ctx->num_internal_frames; i++) {
		u32 y, cb, cr, mvcol;

		/* Start addresses of Y, Cb, Cr planes */
		y = ctx->internal_frames[i].buf.paddr;
		cb = y + ysize;
		cr = y + ysize + ysize/4;
		mvcol = y + ysize + ysize/4 + ysize/4;
		if (ctx->tiled_map_type == GDI_TILED_FRAME_MB_RASTER_MAP) {
			cb = round_up(cb, 4096);
			mvcol = cb + ysize/2;
			cr = 0;
			/* Packed 20-bit MSB of base addresses */
			/* YYYYYCCC, CCyyyyyc, cccc.... */
			y = (y & 0xfffff000) | cb >> 20;
			cb = (cb & 0x000ff000) << 12;
		}
		coda_parabuf_write(ctx, i * 3 + 0, y);
		coda_parabuf_write(ctx, i * 3 + 1, cb);
		coda_parabuf_write(ctx, i * 3 + 2, cr);

		if (dev->devtype->product == CODA_DX6)
			continue;

		/* mvcol buffer for h.264 and mpeg4 */
		if (ctx->codec->src_fourcc == V4L2_PIX_FMT_H264)
			coda_parabuf_write(ctx, 96 + i, mvcol);
		if (ctx->codec->src_fourcc == V4L2_PIX_FMT_MPEG4 && i == 0)
			coda_parabuf_write(ctx, 97, mvcol);
	}

	return 0;
}