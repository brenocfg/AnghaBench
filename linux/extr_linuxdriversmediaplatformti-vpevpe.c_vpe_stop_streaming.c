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
struct vpe_ctx {TYPE_1__* dev; } ;
struct vb2_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vpdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 struct vpe_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vpdma_dump_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpe_dump_regs (TYPE_1__*) ; 
 int /*<<< orphan*/  vpe_return_all_buffers (struct vpe_ctx*,struct vb2_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpe_stop_streaming(struct vb2_queue *q)
{
	struct vpe_ctx *ctx = vb2_get_drv_priv(q);

	vpe_dump_regs(ctx->dev);
	vpdma_dump_regs(ctx->dev->vpdma);

	vpe_return_all_buffers(ctx, q, VB2_BUF_STATE_ERROR);
}