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
struct mtk_mdp_ctx {int /*<<< orphan*/  work; TYPE_1__* mdp_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  job_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_mdp_m2m_device_run(void *priv)
{
	struct mtk_mdp_ctx *ctx = priv;

	queue_work(ctx->mdp_dev->job_wq, &ctx->work);
}