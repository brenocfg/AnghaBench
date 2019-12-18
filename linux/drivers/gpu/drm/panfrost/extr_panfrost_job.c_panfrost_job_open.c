#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct panfrost_job_slot {TYPE_2__* queue; } ;
struct panfrost_file_priv {int /*<<< orphan*/ * sched_entity; struct panfrost_device* pfdev; } ;
struct panfrost_device {struct panfrost_job_slot* js; } ;
struct drm_sched_rq {int dummy; } ;
struct TYPE_3__ {struct drm_sched_rq* sched_rq; } ;
struct TYPE_4__ {TYPE_1__ sched; } ;

/* Variables and functions */
 size_t DRM_SCHED_PRIORITY_NORMAL ; 
 int NUM_JOB_SLOTS ; 
 scalar_t__ WARN_ON (int) ; 
 int drm_sched_entity_init (int /*<<< orphan*/ *,struct drm_sched_rq**,int,int /*<<< orphan*/ *) ; 

int panfrost_job_open(struct panfrost_file_priv *panfrost_priv)
{
	struct panfrost_device *pfdev = panfrost_priv->pfdev;
	struct panfrost_job_slot *js = pfdev->js;
	struct drm_sched_rq *rq;
	int ret, i;

	for (i = 0; i < NUM_JOB_SLOTS; i++) {
		rq = &js->queue[i].sched.sched_rq[DRM_SCHED_PRIORITY_NORMAL];
		ret = drm_sched_entity_init(&panfrost_priv->sched_entity[i], &rq, 1, NULL);
		if (WARN_ON(ret))
			return ret;
	}
	return 0;
}