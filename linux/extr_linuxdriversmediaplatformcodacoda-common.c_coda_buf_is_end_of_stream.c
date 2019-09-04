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
struct vb2_v4l2_buffer {int sequence; } ;
struct coda_ctx {int bit_stream_param; int qsequence; } ;

/* Variables and functions */
 int CODA_BIT_STREAM_END_FLAG ; 

__attribute__((used)) static bool coda_buf_is_end_of_stream(struct coda_ctx *ctx,
				      struct vb2_v4l2_buffer *buf)
{
	return ((ctx->bit_stream_param & CODA_BIT_STREAM_END_FLAG) &&
		(buf->sequence == (ctx->qsequence - 1)));
}