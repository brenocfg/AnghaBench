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
struct mtk_vcodec_dev {int /*<<< orphan*/  enc_mutex; } ;
struct mtk_vcodec_ctx {struct mtk_vcodec_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

int mtk_venc_lock(struct mtk_vcodec_ctx *ctx)
{
	struct mtk_vcodec_dev *dev = ctx->dev;

	mutex_lock(&dev->enc_mutex);
	return 0;
}