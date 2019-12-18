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
struct vb2_buffer {TYPE_1__* planes; } ;
struct TYPE_6__ {TYPE_2__* plane_fmt; } ;
struct hantro_ctx {TYPE_3__ dst_fmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  sizeimage; } ;
struct TYPE_4__ {int /*<<< orphan*/  bytesused; } ;

/* Variables and functions */

__attribute__((used)) static int
hantro_dec_buf_finish(struct hantro_ctx *ctx, struct vb2_buffer *buf,
		      unsigned int bytesused)
{
	/* For decoders set bytesused as per the output picture. */
	buf->planes[0].bytesused = ctx->dst_fmt.plane_fmt[0].sizeimage;
	return 0;
}