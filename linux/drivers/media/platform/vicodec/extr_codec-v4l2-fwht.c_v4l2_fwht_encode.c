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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct v4l2_fwht_state {unsigned int stride; unsigned int coded_height; int gop_cnt; int gop_size; int visible_width; int visible_height; int colorspace; int xfer_func; int ycbcr_enc; int quantization; int /*<<< orphan*/  ref_frame; int /*<<< orphan*/  p_frame_qp; int /*<<< orphan*/  i_frame_qp; struct v4l2_fwht_pixfmt_info* info; } ;
struct v4l2_fwht_pixfmt_info {int planes_num; scalar_t__ id; int components_num; int pixenc; } ;
struct fwht_raw_frame {int height_div; int width_div; } ;
struct fwht_cframe_hdr {void* size; void* quantization; void* ycbcr_enc; void* xfer_func; void* colorspace; void* flags; void* height; void* width; void* version; int /*<<< orphan*/  magic2; int /*<<< orphan*/  magic1; } ;
struct fwht_cframe {int size; int /*<<< orphan*/ * rlc_data; int /*<<< orphan*/  p_frame_qp; int /*<<< orphan*/  i_frame_qp; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int FWHT_ALPHA_UNENCODED ; 
 int FWHT_CB_UNENCODED ; 
 int FWHT_CR_UNENCODED ; 
 int FWHT_FL_ALPHA_IS_UNCOMPRESSED ; 
 int FWHT_FL_CB_IS_UNCOMPRESSED ; 
 int FWHT_FL_CHROMA_FULL_HEIGHT ; 
 int FWHT_FL_CHROMA_FULL_WIDTH ; 
 int FWHT_FL_COMPONENTS_NUM_OFFSET ; 
 int FWHT_FL_CR_IS_UNCOMPRESSED ; 
 int FWHT_FL_I_FRAME ; 
 int FWHT_FL_LUMA_IS_UNCOMPRESSED ; 
 int FWHT_FRAME_PCODED ; 
 int FWHT_LUMA_UNENCODED ; 
 int /*<<< orphan*/  FWHT_MAGIC1 ; 
 int /*<<< orphan*/  FWHT_MAGIC2 ; 
 int FWHT_VERSION ; 
 scalar_t__ V4L2_PIX_FMT_NV24 ; 
 scalar_t__ V4L2_PIX_FMT_NV42 ; 
 int fwht_encode_frame (struct fwht_raw_frame*,int /*<<< orphan*/ *,struct fwht_cframe*,int,int,int,int,unsigned int,unsigned int) ; 
 void* htonl (int) ; 
 scalar_t__ prepare_raw_frame (struct fwht_raw_frame*,struct v4l2_fwht_pixfmt_info const*,int /*<<< orphan*/ *,unsigned int) ; 

int v4l2_fwht_encode(struct v4l2_fwht_state *state, u8 *p_in, u8 *p_out)
{
	unsigned int size = state->stride * state->coded_height;
	unsigned int chroma_stride = state->stride;
	const struct v4l2_fwht_pixfmt_info *info = state->info;
	struct fwht_cframe_hdr *p_hdr;
	struct fwht_cframe cf;
	struct fwht_raw_frame rf;
	u32 encoding;
	u32 flags = 0;

	if (!info)
		return -EINVAL;

	if (prepare_raw_frame(&rf, info, p_in, size))
		return -EINVAL;

	if (info->planes_num == 3)
		chroma_stride /= 2;

	if (info->id == V4L2_PIX_FMT_NV24 ||
	    info->id == V4L2_PIX_FMT_NV42)
		chroma_stride *= 2;

	cf.i_frame_qp = state->i_frame_qp;
	cf.p_frame_qp = state->p_frame_qp;
	cf.rlc_data = (__be16 *)(p_out + sizeof(*p_hdr));

	encoding = fwht_encode_frame(&rf, &state->ref_frame, &cf,
				     !state->gop_cnt,
				     state->gop_cnt == state->gop_size - 1,
				     state->visible_width,
				     state->visible_height,
				     state->stride, chroma_stride);
	if (!(encoding & FWHT_FRAME_PCODED))
		state->gop_cnt = 0;
	if (++state->gop_cnt >= state->gop_size)
		state->gop_cnt = 0;

	p_hdr = (struct fwht_cframe_hdr *)p_out;
	p_hdr->magic1 = FWHT_MAGIC1;
	p_hdr->magic2 = FWHT_MAGIC2;
	p_hdr->version = htonl(FWHT_VERSION);
	p_hdr->width = htonl(state->visible_width);
	p_hdr->height = htonl(state->visible_height);
	flags |= (info->components_num - 1) << FWHT_FL_COMPONENTS_NUM_OFFSET;
	flags |= info->pixenc;
	if (encoding & FWHT_LUMA_UNENCODED)
		flags |= FWHT_FL_LUMA_IS_UNCOMPRESSED;
	if (encoding & FWHT_CB_UNENCODED)
		flags |= FWHT_FL_CB_IS_UNCOMPRESSED;
	if (encoding & FWHT_CR_UNENCODED)
		flags |= FWHT_FL_CR_IS_UNCOMPRESSED;
	if (encoding & FWHT_ALPHA_UNENCODED)
		flags |= FWHT_FL_ALPHA_IS_UNCOMPRESSED;
	if (!(encoding & FWHT_FRAME_PCODED))
		flags |= FWHT_FL_I_FRAME;
	if (rf.height_div == 1)
		flags |= FWHT_FL_CHROMA_FULL_HEIGHT;
	if (rf.width_div == 1)
		flags |= FWHT_FL_CHROMA_FULL_WIDTH;
	p_hdr->flags = htonl(flags);
	p_hdr->colorspace = htonl(state->colorspace);
	p_hdr->xfer_func = htonl(state->xfer_func);
	p_hdr->ycbcr_enc = htonl(state->ycbcr_enc);
	p_hdr->quantization = htonl(state->quantization);
	p_hdr->size = htonl(cf.size);
	return cf.size + sizeof(*p_hdr);
}