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
struct TYPE_8__ {TYPE_3__* m2m_ctx; } ;
struct cedrus_ctx {int /*<<< orphan*/  dst_fmt; TYPE_4__ fh; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {struct vb2_buffer** bufs; } ;
struct TYPE_6__ {TYPE_1__ q; } ;
struct TYPE_7__ {TYPE_2__ cap_q_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  cedrus_buf_addr (struct vb2_buffer*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline dma_addr_t cedrus_dst_buf_addr(struct cedrus_ctx *ctx,
					     int index, unsigned int plane)
{
	struct vb2_buffer *buf;

	if (index < 0)
		return 0;

	buf = ctx->fh.m2m_ctx->cap_q_ctx.q.bufs[index];
	return buf ? cedrus_buf_addr(buf, &ctx->dst_fmt, plane) : 0;
}