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
typedef  int u32 ;
struct vb2_buffer {int dummy; } ;
struct gsc_frame {int f_width; int f_height; TYPE_1__* fmt; } ;
struct gsc_ctx {int dummy; } ;
struct gsc_addr {int cb; void* cr; void* y; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int num_planes; int num_comp; scalar_t__ pixelformat; int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GSC_YUV420 ; 
 scalar_t__ V4L2_PIX_FMT_VYUY ; 
 scalar_t__ V4L2_PIX_FMT_YVU420 ; 
 scalar_t__ V4L2_PIX_FMT_YVU420M ; 
 scalar_t__ V4L2_PIX_FMT_YVYU ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  swap (int,void*) ; 
 void* vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int) ; 

int gsc_prepare_addr(struct gsc_ctx *ctx, struct vb2_buffer *vb,
			struct gsc_frame *frame, struct gsc_addr *addr)
{
	int ret = 0;
	u32 pix_size;

	if ((vb == NULL) || (frame == NULL))
		return -EINVAL;

	pix_size = frame->f_width * frame->f_height;

	pr_debug("num_planes= %d, num_comp= %d, pix_size= %d",
		frame->fmt->num_planes, frame->fmt->num_comp, pix_size);

	addr->y = vb2_dma_contig_plane_dma_addr(vb, 0);

	if (frame->fmt->num_planes == 1) {
		switch (frame->fmt->num_comp) {
		case 1:
			addr->cb = 0;
			addr->cr = 0;
			break;
		case 2:
			/* decompose Y into Y/Cb */
			addr->cb = (dma_addr_t)(addr->y + pix_size);
			addr->cr = 0;
			break;
		case 3:
			/* decompose Y into Y/Cb/Cr */
			addr->cb = (dma_addr_t)(addr->y + pix_size);
			if (GSC_YUV420 == frame->fmt->color)
				addr->cr = (dma_addr_t)(addr->cb
						+ (pix_size >> 2));
			else /* 422 */
				addr->cr = (dma_addr_t)(addr->cb
						+ (pix_size >> 1));
			break;
		default:
			pr_err("Invalid the number of color planes");
			return -EINVAL;
		}
	} else {
		if (frame->fmt->num_planes >= 2)
			addr->cb = vb2_dma_contig_plane_dma_addr(vb, 1);

		if (frame->fmt->num_planes == 3)
			addr->cr = vb2_dma_contig_plane_dma_addr(vb, 2);
	}

	if ((frame->fmt->pixelformat == V4L2_PIX_FMT_VYUY) ||
		(frame->fmt->pixelformat == V4L2_PIX_FMT_YVYU) ||
		(frame->fmt->pixelformat == V4L2_PIX_FMT_YVU420) ||
		(frame->fmt->pixelformat == V4L2_PIX_FMT_YVU420M))
		swap(addr->cb, addr->cr);

	pr_debug("ADDR: y= %pad  cb= %pad cr= %pad ret= %d",
		&addr->y, &addr->cb, &addr->cr, ret);

	return ret;
}