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
struct msm_file_private {int /*<<< orphan*/  queuelock; int /*<<< orphan*/  submitqueues; } ;
struct msm_drm_private {TYPE_1__* gpu; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {scalar_t__ nr_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int clamp_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int msm_submitqueue_create (struct drm_device*,struct msm_file_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uint32_t ; 

int msm_submitqueue_init(struct drm_device *drm, struct msm_file_private *ctx)
{
	struct msm_drm_private *priv = drm->dev_private;
	int default_prio;

	if (!ctx)
		return 0;

	/*
	 * Select priority 2 as the "default priority" unless nr_rings is less
	 * than 2 and then pick the lowest pirority
	 */
	default_prio = priv->gpu ?
		clamp_t(uint32_t, 2, 0, priv->gpu->nr_rings - 1) : 0;

	INIT_LIST_HEAD(&ctx->submitqueues);

	rwlock_init(&ctx->queuelock);

	return msm_submitqueue_create(drm, ctx, default_prio, 0, NULL);
}