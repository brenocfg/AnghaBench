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
typedef  scalar_t__ u32 ;
struct vb2_v4l2_buffer {scalar_t__ sequence; int /*<<< orphan*/  vb2_buf; } ;
struct coda_ctx {int /*<<< orphan*/  qsequence; int /*<<< orphan*/  bitstream_fifo; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ kfifo_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vb2_get_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_bitstream_queue(struct coda_ctx *ctx,
				struct vb2_v4l2_buffer *src_buf)
{
	u32 src_size = vb2_get_plane_payload(&src_buf->vb2_buf, 0);
	u32 n;

	n = kfifo_in(&ctx->bitstream_fifo,
			vb2_plane_vaddr(&src_buf->vb2_buf, 0), src_size);
	if (n < src_size)
		return -ENOSPC;

	src_buf->sequence = ctx->qsequence++;

	return 0;
}