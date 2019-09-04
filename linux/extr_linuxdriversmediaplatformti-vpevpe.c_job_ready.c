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
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vpe_ctx {TYPE_1__ fh; } ;

/* Variables and functions */
 scalar_t__ v4l2_m2m_num_dst_bufs_ready (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_m2m_num_src_bufs_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int job_ready(void *priv)
{
	struct vpe_ctx *ctx = priv;

	/*
	 * This check is needed as this might be called directly from driver
	 * When called by m2m framework, this will always satisfy, but when
	 * called from vpe_irq, this might fail. (src stream with zero buffers)
	 */
	if (v4l2_m2m_num_src_bufs_ready(ctx->fh.m2m_ctx) <= 0 ||
		v4l2_m2m_num_dst_bufs_ready(ctx->fh.m2m_ctx) <= 0)
		return 0;

	return 1;
}