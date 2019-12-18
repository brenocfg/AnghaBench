#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {void* up_scale_factor; void* down_scale_factor; } ;
union rga_src_y_factor {void* val; TYPE_5__ data; } ;
struct TYPE_21__ {void* up_scale_factor; void* down_scale_factor; } ;
union rga_src_x_factor {void* val; TYPE_4__ data; } ;
struct TYPE_23__ {int vir_stride; int vir_width; } ;
union rga_src_vir_info {void* val; TYPE_6__ data; } ;
struct TYPE_14__ {scalar_t__ format; scalar_t__ rot_mode; int /*<<< orphan*/  mir_mode; int /*<<< orphan*/  vscl_mode; int /*<<< orphan*/  hscl_mode; void* csc_mode; int /*<<< orphan*/  swap; } ;
union rga_src_info {void* val; TYPE_10__ data; } ;
struct TYPE_24__ {unsigned int act_height; unsigned int act_width; } ;
union rga_src_act_info {void* val; TYPE_7__ data; } ;
struct TYPE_25__ {int vir_stride; } ;
union rga_dst_vir_info {void* val; TYPE_8__ data; } ;
struct TYPE_19__ {scalar_t__ format; void* csc_mode; int /*<<< orphan*/  swap; } ;
union rga_dst_info {void* val; TYPE_2__ data; } ;
struct TYPE_26__ {unsigned int act_height; unsigned int act_width; } ;
union rga_dst_act_info {void* val; TYPE_9__ data; } ;
typedef  void* u32 ;
struct TYPE_20__ {scalar_t__ major; scalar_t__ minor; } ;
struct rockchip_rga {void** cmdbuf_virt; TYPE_3__ version; } ;
struct TYPE_16__ {unsigned int height; unsigned int width; unsigned int left; unsigned int top; } ;
struct TYPE_17__ {int colorspace; int stride; TYPE_1__* fmt; TYPE_12__ crop; } ;
struct rga_ctx {int rotate; TYPE_13__ out; TYPE_13__ in; scalar_t__ hflip; scalar_t__ vflip; struct rockchip_rga* rga; } ;
struct TYPE_15__ {void* v_off; void* u_off; void* y_off; } ;
struct rga_corners_addr_offset {TYPE_11__ left_top; } ;
struct rga_addr_offset {void* v_off; void* u_off; void* y_off; } ;
struct TYPE_18__ {scalar_t__ hw_format; int /*<<< orphan*/  color_swap; } ;

/* Variables and functions */
 scalar_t__ RGA_COLOR_FMT_YUV422SP ; 
 int RGA_DST_ACT_INFO ; 
 int RGA_DST_CB_BASE_ADDR ; 
 int RGA_DST_CR_BASE_ADDR ; 
 void* RGA_DST_CSC_MODE_BT601_R0 ; 
 int RGA_DST_INFO ; 
 int RGA_DST_VIR_INFO ; 
 int RGA_DST_Y_RGB_BASE_ADDR ; 
 int RGA_MODE_BASE_REG ; 
 int RGA_SRC_ACT_INFO ; 
 int RGA_SRC_CB_BASE_ADDR ; 
 int RGA_SRC_CR_BASE_ADDR ; 
 void* RGA_SRC_CSC_MODE_BT601_R0 ; 
 void* RGA_SRC_CSC_MODE_BT709_R0 ; 
 int /*<<< orphan*/  RGA_SRC_HSCL_MODE_DOWN ; 
 int /*<<< orphan*/  RGA_SRC_HSCL_MODE_NO ; 
 int /*<<< orphan*/  RGA_SRC_HSCL_MODE_UP ; 
 int RGA_SRC_INFO ; 
 int /*<<< orphan*/  RGA_SRC_MIRR_MODE_X ; 
 int /*<<< orphan*/  RGA_SRC_MIRR_MODE_Y ; 
 scalar_t__ RGA_SRC_ROT_MODE_0_DEGREE ; 
 scalar_t__ RGA_SRC_ROT_MODE_180_DEGREE ; 
 scalar_t__ RGA_SRC_ROT_MODE_270_DEGREE ; 
 scalar_t__ RGA_SRC_ROT_MODE_90_DEGREE ; 
 int RGA_SRC_VIR_INFO ; 
 int /*<<< orphan*/  RGA_SRC_VSCL_MODE_DOWN ; 
 int /*<<< orphan*/  RGA_SRC_VSCL_MODE_NO ; 
 int /*<<< orphan*/  RGA_SRC_VSCL_MODE_UP ; 
 int RGA_SRC_X_FACTOR ; 
 int RGA_SRC_Y_FACTOR ; 
 int RGA_SRC_Y_RGB_BASE_ADDR ; 
#define  V4L2_COLORSPACE_REC709 128 
 int abs (unsigned int) ; 
 struct rga_corners_addr_offset rga_get_addr_offset (TYPE_13__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 void* rga_get_scaling (unsigned int,unsigned int) ; 
 struct rga_addr_offset* rga_lookup_draw_pos (struct rga_corners_addr_offset*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rga_cmd_set_trans_info(struct rga_ctx *ctx)
{
	struct rockchip_rga *rga = ctx->rga;
	u32 *dest = rga->cmdbuf_virt;
	unsigned int scale_dst_w, scale_dst_h;
	unsigned int src_h, src_w, src_x, src_y, dst_h, dst_w, dst_x, dst_y;
	union rga_src_info src_info;
	union rga_dst_info dst_info;
	union rga_src_x_factor x_factor;
	union rga_src_y_factor y_factor;
	union rga_src_vir_info src_vir_info;
	union rga_src_act_info src_act_info;
	union rga_dst_vir_info dst_vir_info;
	union rga_dst_act_info dst_act_info;

	struct rga_addr_offset *dst_offset;
	struct rga_corners_addr_offset offsets;
	struct rga_corners_addr_offset src_offsets;

	src_h = ctx->in.crop.height;
	src_w = ctx->in.crop.width;
	src_x = ctx->in.crop.left;
	src_y = ctx->in.crop.top;
	dst_h = ctx->out.crop.height;
	dst_w = ctx->out.crop.width;
	dst_x = ctx->out.crop.left;
	dst_y = ctx->out.crop.top;

	src_info.val = dest[(RGA_SRC_INFO - RGA_MODE_BASE_REG) >> 2];
	dst_info.val = dest[(RGA_DST_INFO - RGA_MODE_BASE_REG) >> 2];
	x_factor.val = dest[(RGA_SRC_X_FACTOR - RGA_MODE_BASE_REG) >> 2];
	y_factor.val = dest[(RGA_SRC_Y_FACTOR - RGA_MODE_BASE_REG) >> 2];
	src_vir_info.val = dest[(RGA_SRC_VIR_INFO - RGA_MODE_BASE_REG) >> 2];
	src_act_info.val = dest[(RGA_SRC_ACT_INFO - RGA_MODE_BASE_REG) >> 2];
	dst_vir_info.val = dest[(RGA_DST_VIR_INFO - RGA_MODE_BASE_REG) >> 2];
	dst_act_info.val = dest[(RGA_DST_ACT_INFO - RGA_MODE_BASE_REG) >> 2];

	src_info.data.format = ctx->in.fmt->hw_format;
	src_info.data.swap = ctx->in.fmt->color_swap;
	dst_info.data.format = ctx->out.fmt->hw_format;
	dst_info.data.swap = ctx->out.fmt->color_swap;

	if (ctx->in.fmt->hw_format >= RGA_COLOR_FMT_YUV422SP) {
		if (ctx->out.fmt->hw_format < RGA_COLOR_FMT_YUV422SP) {
			switch (ctx->in.colorspace) {
			case V4L2_COLORSPACE_REC709:
				src_info.data.csc_mode =
					RGA_SRC_CSC_MODE_BT709_R0;
				break;
			default:
				src_info.data.csc_mode =
					RGA_SRC_CSC_MODE_BT601_R0;
				break;
			}
		}
	}

	if (ctx->out.fmt->hw_format >= RGA_COLOR_FMT_YUV422SP) {
		switch (ctx->out.colorspace) {
		case V4L2_COLORSPACE_REC709:
			dst_info.data.csc_mode = RGA_SRC_CSC_MODE_BT709_R0;
			break;
		default:
			dst_info.data.csc_mode = RGA_DST_CSC_MODE_BT601_R0;
			break;
		}
	}

	if (ctx->vflip)
		src_info.data.mir_mode |= RGA_SRC_MIRR_MODE_X;

	if (ctx->hflip)
		src_info.data.mir_mode |= RGA_SRC_MIRR_MODE_Y;

	switch (ctx->rotate) {
	case 90:
		src_info.data.rot_mode = RGA_SRC_ROT_MODE_90_DEGREE;
		break;
	case 180:
		src_info.data.rot_mode = RGA_SRC_ROT_MODE_180_DEGREE;
		break;
	case 270:
		src_info.data.rot_mode = RGA_SRC_ROT_MODE_270_DEGREE;
		break;
	default:
		src_info.data.rot_mode = RGA_SRC_ROT_MODE_0_DEGREE;
		break;
	}

	/*
	 * Calculate the up/down scaling mode/factor.
	 *
	 * RGA used to scale the picture first, and then rotate second,
	 * so we need to swap the w/h when rotate degree is 90/270.
	 */
	if (src_info.data.rot_mode == RGA_SRC_ROT_MODE_90_DEGREE ||
	    src_info.data.rot_mode == RGA_SRC_ROT_MODE_270_DEGREE) {
		if (rga->version.major == 0 || rga->version.minor == 0) {
			if (dst_w == src_h)
				src_h -= 8;
			if (abs(src_w - dst_h) < 16)
				src_w -= 16;
		}

		scale_dst_h = dst_w;
		scale_dst_w = dst_h;
	} else {
		scale_dst_w = dst_w;
		scale_dst_h = dst_h;
	}

	if (src_w == scale_dst_w) {
		src_info.data.hscl_mode = RGA_SRC_HSCL_MODE_NO;
		x_factor.val = 0;
	} else if (src_w > scale_dst_w) {
		src_info.data.hscl_mode = RGA_SRC_HSCL_MODE_DOWN;
		x_factor.data.down_scale_factor =
			rga_get_scaling(src_w, scale_dst_w) + 1;
	} else {
		src_info.data.hscl_mode = RGA_SRC_HSCL_MODE_UP;
		x_factor.data.up_scale_factor =
			rga_get_scaling(src_w - 1, scale_dst_w - 1);
	}

	if (src_h == scale_dst_h) {
		src_info.data.vscl_mode = RGA_SRC_VSCL_MODE_NO;
		y_factor.val = 0;
	} else if (src_h > scale_dst_h) {
		src_info.data.vscl_mode = RGA_SRC_VSCL_MODE_DOWN;
		y_factor.data.down_scale_factor =
			rga_get_scaling(src_h, scale_dst_h) + 1;
	} else {
		src_info.data.vscl_mode = RGA_SRC_VSCL_MODE_UP;
		y_factor.data.up_scale_factor =
			rga_get_scaling(src_h - 1, scale_dst_h - 1);
	}

	/*
	 * Calculate the framebuffer virtual strides and active size,
	 * note that the step of vir_stride / vir_width is 4 byte words
	 */
	src_vir_info.data.vir_stride = ctx->in.stride >> 2;
	src_vir_info.data.vir_width = ctx->in.stride >> 2;

	src_act_info.data.act_height = src_h - 1;
	src_act_info.data.act_width = src_w - 1;

	dst_vir_info.data.vir_stride = ctx->out.stride >> 2;
	dst_act_info.data.act_height = dst_h - 1;
	dst_act_info.data.act_width = dst_w - 1;

	/*
	 * Calculate the source framebuffer base address with offset pixel.
	 */
	src_offsets = rga_get_addr_offset(&ctx->in, src_x, src_y,
					  src_w, src_h);

	/*
	 * Configure the dest framebuffer base address with pixel offset.
	 */
	offsets = rga_get_addr_offset(&ctx->out, dst_x, dst_y, dst_w, dst_h);
	dst_offset = rga_lookup_draw_pos(&offsets, src_info.data.rot_mode,
					 src_info.data.mir_mode);

	dest[(RGA_SRC_Y_RGB_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		src_offsets.left_top.y_off;
	dest[(RGA_SRC_CB_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		src_offsets.left_top.u_off;
	dest[(RGA_SRC_CR_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		src_offsets.left_top.v_off;

	dest[(RGA_SRC_X_FACTOR - RGA_MODE_BASE_REG) >> 2] = x_factor.val;
	dest[(RGA_SRC_Y_FACTOR - RGA_MODE_BASE_REG) >> 2] = y_factor.val;
	dest[(RGA_SRC_VIR_INFO - RGA_MODE_BASE_REG) >> 2] = src_vir_info.val;
	dest[(RGA_SRC_ACT_INFO - RGA_MODE_BASE_REG) >> 2] = src_act_info.val;

	dest[(RGA_SRC_INFO - RGA_MODE_BASE_REG) >> 2] = src_info.val;

	dest[(RGA_DST_Y_RGB_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		dst_offset->y_off;
	dest[(RGA_DST_CB_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		dst_offset->u_off;
	dest[(RGA_DST_CR_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		dst_offset->v_off;

	dest[(RGA_DST_VIR_INFO - RGA_MODE_BASE_REG) >> 2] = dst_vir_info.val;
	dest[(RGA_DST_ACT_INFO - RGA_MODE_BASE_REG) >> 2] = dst_act_info.val;

	dest[(RGA_DST_INFO - RGA_MODE_BASE_REG) >> 2] = dst_info.val;
}