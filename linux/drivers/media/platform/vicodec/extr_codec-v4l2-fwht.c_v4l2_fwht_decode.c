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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct fwht_raw_frame {int /*<<< orphan*/ * buf; } ;
struct TYPE_2__ {scalar_t__ magic1; scalar_t__ magic2; int /*<<< orphan*/  size; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  flags; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  version; } ;
struct v4l2_fwht_state {unsigned int stride; unsigned int ref_stride; unsigned int coded_height; void* visible_width; void* visible_height; struct fwht_raw_frame ref_frame; TYPE_1__ header; void* quantization; void* ycbcr_enc; void* xfer_func; void* colorspace; struct v4l2_fwht_pixfmt_info* info; } ;
struct v4l2_fwht_pixfmt_info {int pixenc; unsigned int components_num; unsigned int width_div; unsigned int height_div; int planes_num; scalar_t__ id; } ;
struct fwht_cframe {void* size; int /*<<< orphan*/ * rlc_data; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int FWHT_FL_CHROMA_FULL_HEIGHT ; 
 int FWHT_FL_CHROMA_FULL_WIDTH ; 
 int FWHT_FL_COMPONENTS_NUM_MSK ; 
 int FWHT_FL_COMPONENTS_NUM_OFFSET ; 
 int FWHT_FL_PIXENC_MSK ; 
 scalar_t__ FWHT_MAGIC1 ; 
 scalar_t__ FWHT_MAGIC2 ; 
 unsigned int FWHT_VERSION ; 
 scalar_t__ V4L2_PIX_FMT_NV24 ; 
 scalar_t__ V4L2_PIX_FMT_NV42 ; 
 int /*<<< orphan*/  fwht_decode_frame (struct fwht_cframe*,int,unsigned int,void*,void*,struct fwht_raw_frame*,unsigned int,unsigned int,struct fwht_raw_frame*,unsigned int,unsigned int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 
 scalar_t__ prepare_raw_frame (struct fwht_raw_frame*,struct v4l2_fwht_pixfmt_info const*,int /*<<< orphan*/ *,unsigned int) ; 

int v4l2_fwht_decode(struct v4l2_fwht_state *state, u8 *p_in, u8 *p_out)
{
	u32 flags;
	struct fwht_cframe cf;
	unsigned int components_num = 3;
	unsigned int version;
	const struct v4l2_fwht_pixfmt_info *info;
	unsigned int hdr_width_div, hdr_height_div;
	struct fwht_raw_frame dst_rf;
	unsigned int dst_chroma_stride = state->stride;
	unsigned int ref_chroma_stride = state->ref_stride;
	unsigned int dst_size = state->stride * state->coded_height;
	unsigned int ref_size;

	if (!state->info)
		return -EINVAL;

	info = state->info;

	version = ntohl(state->header.version);
	if (!version || version > FWHT_VERSION) {
		pr_err("version %d is not supported, current version is %d\n",
		       version, FWHT_VERSION);
		return -EINVAL;
	}

	if (state->header.magic1 != FWHT_MAGIC1 ||
	    state->header.magic2 != FWHT_MAGIC2)
		return -EINVAL;

	/* TODO: support resolution changes */
	if (ntohl(state->header.width)  != state->visible_width ||
	    ntohl(state->header.height) != state->visible_height)
		return -EINVAL;

	flags = ntohl(state->header.flags);

	if (version >= 2) {
		if ((flags & FWHT_FL_PIXENC_MSK) != info->pixenc)
			return -EINVAL;
		components_num = 1 + ((flags & FWHT_FL_COMPONENTS_NUM_MSK) >>
				FWHT_FL_COMPONENTS_NUM_OFFSET);
	}

	if (components_num != info->components_num)
		return -EINVAL;

	state->colorspace = ntohl(state->header.colorspace);
	state->xfer_func = ntohl(state->header.xfer_func);
	state->ycbcr_enc = ntohl(state->header.ycbcr_enc);
	state->quantization = ntohl(state->header.quantization);
	cf.rlc_data = (__be16 *)p_in;
	cf.size = ntohl(state->header.size);

	hdr_width_div = (flags & FWHT_FL_CHROMA_FULL_WIDTH) ? 1 : 2;
	hdr_height_div = (flags & FWHT_FL_CHROMA_FULL_HEIGHT) ? 1 : 2;
	if (hdr_width_div != info->width_div ||
	    hdr_height_div != info->height_div)
		return -EINVAL;

	if (prepare_raw_frame(&dst_rf, info, p_out, dst_size))
		return -EINVAL;
	if (info->planes_num == 3) {
		dst_chroma_stride /= 2;
		ref_chroma_stride /= 2;
	}
	if (info->id == V4L2_PIX_FMT_NV24 ||
	    info->id == V4L2_PIX_FMT_NV42) {
		dst_chroma_stride *= 2;
		ref_chroma_stride *= 2;
	}


	ref_size = state->ref_stride * state->coded_height;

	if (prepare_raw_frame(&state->ref_frame, info, state->ref_frame.buf,
			      ref_size))
		return -EINVAL;

	if (!fwht_decode_frame(&cf, flags, components_num,
			state->visible_width, state->visible_height,
			&state->ref_frame, state->ref_stride, ref_chroma_stride,
			&dst_rf, state->stride, dst_chroma_stride))
		return -EINVAL;
	return 0;
}