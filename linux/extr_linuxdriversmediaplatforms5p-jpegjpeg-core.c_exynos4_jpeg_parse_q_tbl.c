#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_5__ {int n; int* len; scalar_t__* marker; } ;
struct TYPE_6__ {TYPE_2__ dqt; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct s5p_jpeg_ctx {TYPE_3__ out_q; TYPE_1__ fh; struct s5p_jpeg* jpeg; } ;
struct s5p_jpeg_buffer {int size; int curr; scalar_t__ data; } ;
struct s5p_jpeg {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ EXYNOS4_QTBL_CONTENT (char) ; 
 int get_byte (struct s5p_jpeg_buffer*) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void exynos4_jpeg_parse_q_tbl(struct s5p_jpeg_ctx *ctx)
{
	struct s5p_jpeg *jpeg = ctx->jpeg;
	struct vb2_v4l2_buffer *vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	struct s5p_jpeg_buffer jpeg_buffer;
	unsigned int word;
	int c, i, j;

	for (j = 0; j < ctx->out_q.dqt.n; ++j) {
		jpeg_buffer.size = ctx->out_q.dqt.len[j];
		jpeg_buffer.data = (unsigned long)vb2_plane_vaddr(&vb->vb2_buf, 0) +
				   ctx->out_q.dqt.marker[j];
		jpeg_buffer.curr = 0;

		word = 0;
		while (jpeg_buffer.size - jpeg_buffer.curr >= 65) {
			char id;

			c = get_byte(&jpeg_buffer);
			if (c == -1)
				return;
			id = c & 0xf;
			/* nonzero means extended mode - not supported */
			if ((c >> 4) & 0xf)
				return;
			for (i = 0; i < 64; ++i) {
				c = get_byte(&jpeg_buffer);
				if (c == -1)
					return;
				word |= c << ((i % 4) * 8);
				if ((i + 1) % 4 == 0) {
					writel(word, jpeg->regs +
					EXYNOS4_QTBL_CONTENT(id) + (i / 4) * 4);
					word = 0;
				}
			}
			word = 0;
		}
	}
}