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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct cedrus_dev {TYPE_1__** dec_ops; } ;
struct cedrus_ctx {size_t current_codec; struct cedrus_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct cedrus_ctx*) ;} ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  cedrus_queue_cleanup (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cedrus_ctx*) ; 
 struct cedrus_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void cedrus_stop_streaming(struct vb2_queue *vq)
{
	struct cedrus_ctx *ctx = vb2_get_drv_priv(vq);
	struct cedrus_dev *dev = ctx->dev;

	if (V4L2_TYPE_IS_OUTPUT(vq->type) &&
	    dev->dec_ops[ctx->current_codec]->stop)
		dev->dec_ops[ctx->current_codec]->stop(ctx);

	cedrus_queue_cleanup(vq, VB2_BUF_STATE_ERROR);
}