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
struct mtk_vcodec_dev {int /*<<< orphan*/  decode_workqueue; } ;
struct mtk_vcodec_ctx {int /*<<< orphan*/  decode_work; struct mtk_vcodec_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void m2mops_vdec_device_run(void *priv)
{
	struct mtk_vcodec_ctx *ctx = priv;
	struct mtk_vcodec_dev *dev = ctx->dev;

	queue_work(dev->decode_workqueue, &ctx->decode_work);
}