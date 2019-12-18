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
struct vb2_buffer {int dummy; } ;
struct cedrus_h264_sram_ref_pic {void* mv_col_bot_ptr; void* mv_col_top_ptr; void* chroma_ptr; void* luma_ptr; void* frame_info; void* bottom_field_order_cnt; void* top_field_order_cnt; } ;
struct cedrus_ctx {int /*<<< orphan*/  dst_fmt; } ;
struct TYPE_7__ {unsigned int position; int pic_type; } ;
struct TYPE_8__ {TYPE_3__ h264; } ;
struct TYPE_5__ {struct vb2_buffer vb2_buf; } ;
struct TYPE_6__ {TYPE_1__ vb; } ;
struct cedrus_buffer {TYPE_4__ codec; TYPE_2__ m2m_buf; } ;

/* Variables and functions */
 int cedrus_buf_addr (struct vb2_buffer*,int /*<<< orphan*/ *,int) ; 
 int cedrus_h264_mv_col_buf_addr (struct cedrus_ctx*,unsigned int,int) ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void cedrus_fill_ref_pic(struct cedrus_ctx *ctx,
				struct cedrus_buffer *buf,
				unsigned int top_field_order_cnt,
				unsigned int bottom_field_order_cnt,
				struct cedrus_h264_sram_ref_pic *pic)
{
	struct vb2_buffer *vbuf = &buf->m2m_buf.vb.vb2_buf;
	unsigned int position = buf->codec.h264.position;

	pic->top_field_order_cnt = cpu_to_le32(top_field_order_cnt);
	pic->bottom_field_order_cnt = cpu_to_le32(bottom_field_order_cnt);
	pic->frame_info = cpu_to_le32(buf->codec.h264.pic_type << 8);

	pic->luma_ptr = cpu_to_le32(cedrus_buf_addr(vbuf, &ctx->dst_fmt, 0));
	pic->chroma_ptr = cpu_to_le32(cedrus_buf_addr(vbuf, &ctx->dst_fmt, 1));
	pic->mv_col_top_ptr =
		cpu_to_le32(cedrus_h264_mv_col_buf_addr(ctx, position, 0));
	pic->mv_col_bot_ptr =
		cpu_to_le32(cedrus_h264_mv_col_buf_addr(ctx, position, 1));
}