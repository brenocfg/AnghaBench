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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vicodec_ctx {int comp_has_frame; int comp_has_next_frame; int cur_buf_offset; int comp_size; size_t comp_magic_cnt; int* compressed_frame; scalar_t__ comp_frame_size; scalar_t__ comp_max_size; TYPE_1__ fh; scalar_t__ is_enc; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct cframe_hdr {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  magic ;

/* Variables and functions */
 int VB2_BUF_STATE_DONE ; 
 int VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  job_remove_out_buf (struct vicodec_ctx*,int) ; 
 int* memchr (int*,int const,int) ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 int vb2_get_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int job_ready(void *priv)
{
	static const u8 magic[] = {
		0x4f, 0x4f, 0x4f, 0x4f, 0xff, 0xff, 0xff, 0xff
	};
	struct vicodec_ctx *ctx = priv;
	struct vb2_v4l2_buffer *src_buf;
	u8 *p_out;
	u8 *p;
	u32 sz;
	u32 state;

	if (ctx->is_enc || ctx->comp_has_frame)
		return 1;

restart:
	ctx->comp_has_next_frame = false;
	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	if (!src_buf)
		return 0;
	p_out = vb2_plane_vaddr(&src_buf->vb2_buf, 0);
	sz = vb2_get_plane_payload(&src_buf->vb2_buf, 0);
	p = p_out + ctx->cur_buf_offset;

	state = VB2_BUF_STATE_DONE;

	if (!ctx->comp_size) {
		state = VB2_BUF_STATE_ERROR;
		for (; p < p_out + sz; p++) {
			u32 copy;

			p = memchr(p, magic[ctx->comp_magic_cnt],
				   p_out + sz - p);
			if (!p) {
				ctx->comp_magic_cnt = 0;
				break;
			}
			copy = sizeof(magic) - ctx->comp_magic_cnt;
			if (p_out + sz - p < copy)
				copy = p_out + sz - p;
			memcpy(ctx->compressed_frame + ctx->comp_magic_cnt,
			       p, copy);
			ctx->comp_magic_cnt += copy;
			if (!memcmp(ctx->compressed_frame, magic, ctx->comp_magic_cnt)) {
				p += copy;
				state = VB2_BUF_STATE_DONE;
				break;
			}
			ctx->comp_magic_cnt = 0;
		}
		if (ctx->comp_magic_cnt < sizeof(magic)) {
			job_remove_out_buf(ctx, state);
			goto restart;
		}
		ctx->comp_size = sizeof(magic);
	}
	if (ctx->comp_size < sizeof(struct cframe_hdr)) {
		struct cframe_hdr *p_hdr = (struct cframe_hdr *)ctx->compressed_frame;
		u32 copy = sizeof(struct cframe_hdr) - ctx->comp_size;

		if (copy > p_out + sz - p)
			copy = p_out + sz - p;
		memcpy(ctx->compressed_frame + ctx->comp_size,
		       p, copy);
		p += copy;
		ctx->comp_size += copy;
		if (ctx->comp_size < sizeof(struct cframe_hdr)) {
			job_remove_out_buf(ctx, state);
			goto restart;
		}
		ctx->comp_frame_size = ntohl(p_hdr->size) + sizeof(*p_hdr);
		if (ctx->comp_frame_size > ctx->comp_max_size)
			ctx->comp_frame_size = ctx->comp_max_size;
	}
	if (ctx->comp_size < ctx->comp_frame_size) {
		u32 copy = ctx->comp_frame_size - ctx->comp_size;

		if (copy > p_out + sz - p)
			copy = p_out + sz - p;
		memcpy(ctx->compressed_frame + ctx->comp_size,
		       p, copy);
		p += copy;
		ctx->comp_size += copy;
		if (ctx->comp_size < ctx->comp_frame_size) {
			job_remove_out_buf(ctx, state);
			goto restart;
		}
	}
	ctx->cur_buf_offset = p - p_out;
	ctx->comp_has_frame = true;
	ctx->comp_has_next_frame = false;
	if (sz - ctx->cur_buf_offset >= sizeof(struct cframe_hdr)) {
		struct cframe_hdr *p_hdr = (struct cframe_hdr *)p;
		u32 frame_size = ntohl(p_hdr->size);
		u32 remaining = sz - ctx->cur_buf_offset - sizeof(*p_hdr);

		if (!memcmp(p, magic, sizeof(magic)))
			ctx->comp_has_next_frame = remaining >= frame_size;
	}
	return 1;
}