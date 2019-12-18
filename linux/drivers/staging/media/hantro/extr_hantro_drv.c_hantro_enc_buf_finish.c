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
struct vb2_buffer {TYPE_1__* planes; } ;
struct TYPE_7__ {scalar_t__ cpu; } ;
struct TYPE_8__ {TYPE_3__ bounce_buffer; } ;
struct hantro_ctx {TYPE_2__* vpu_dst_fmt; TYPE_4__ jpeg_enc; } ;
struct TYPE_6__ {size_t header_size; } ;
struct TYPE_5__ {size_t bytesused; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (size_t,scalar_t__,unsigned int) ; 
 size_t vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 size_t vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hantro_enc_buf_finish(struct hantro_ctx *ctx, struct vb2_buffer *buf,
		      unsigned int bytesused)
{
	size_t avail_size;

	avail_size = vb2_plane_size(buf, 0) - ctx->vpu_dst_fmt->header_size;
	if (bytesused > avail_size)
		return -EINVAL;
	/*
	 * The bounce buffer is only for the JPEG encoder.
	 * TODO: Rework the JPEG encoder to eliminate the need
	 * for a bounce buffer.
	 */
	if (ctx->jpeg_enc.bounce_buffer.cpu) {
		memcpy(vb2_plane_vaddr(buf, 0) +
		       ctx->vpu_dst_fmt->header_size,
		       ctx->jpeg_enc.bounce_buffer.cpu, bytesused);
	}
	buf->planes[0].bytesused =
		ctx->vpu_dst_fmt->header_size + bytesused;
	return 0;
}