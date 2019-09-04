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
struct vb2_queue {int dummy; } ;
struct rockchip_rga {int /*<<< orphan*/  dev; } ;
struct rga_ctx {struct rockchip_rga* rga; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rga_buf_return_buffers (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 struct rga_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void rga_buf_stop_streaming(struct vb2_queue *q)
{
	struct rga_ctx *ctx = vb2_get_drv_priv(q);
	struct rockchip_rga *rga = ctx->rga;

	rga_buf_return_buffers(q, VB2_BUF_STATE_ERROR);
	pm_runtime_put(rga->dev);
}