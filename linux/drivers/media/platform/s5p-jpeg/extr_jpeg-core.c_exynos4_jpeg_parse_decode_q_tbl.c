#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_4__ {scalar_t__ sof; int /*<<< orphan*/  sof_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct s5p_jpeg_ctx {TYPE_2__ out_q; TYPE_1__ fh; struct s5p_jpeg* jpeg; } ;
struct s5p_jpeg_buffer {scalar_t__ curr; scalar_t__ data; int /*<<< orphan*/  size; } ;
struct s5p_jpeg {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos4_jpeg_select_dec_q_tbl (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_dec_components (int /*<<< orphan*/ ,int) ; 
 int get_byte (struct s5p_jpeg_buffer*) ; 
 int /*<<< orphan*/  skip (struct s5p_jpeg_buffer*,int) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos4_jpeg_parse_decode_q_tbl(struct s5p_jpeg_ctx *ctx)
{
	struct s5p_jpeg *jpeg = ctx->jpeg;
	struct vb2_v4l2_buffer *vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	struct s5p_jpeg_buffer jpeg_buffer;
	int c, x, components;

	jpeg_buffer.size = ctx->out_q.sof_len;
	jpeg_buffer.data =
		(unsigned long)vb2_plane_vaddr(&vb->vb2_buf, 0) + ctx->out_q.sof;
	jpeg_buffer.curr = 0;

	skip(&jpeg_buffer, 5); /* P, Y, X */
	components = get_byte(&jpeg_buffer);
	if (components == -1)
		return;

	exynos4_jpeg_set_dec_components(jpeg->regs, components);

	while (components--) {
		c = get_byte(&jpeg_buffer);
		if (c == -1)
			return;
		skip(&jpeg_buffer, 1);
		x = get_byte(&jpeg_buffer);
		if (x == -1)
			return;
		exynos4_jpeg_select_dec_q_tbl(jpeg->regs, c, x);
	}
}