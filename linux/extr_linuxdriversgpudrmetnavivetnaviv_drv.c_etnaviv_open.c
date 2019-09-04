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
struct TYPE_2__ {struct drm_sched_rq* sched_rq; } ;
struct etnaviv_gpu {TYPE_1__ sched; } ;
struct etnaviv_file_private {int /*<<< orphan*/ * sched_entity; } ;
struct etnaviv_drm_private {struct etnaviv_gpu** gpu; } ;
struct drm_sched_rq {int dummy; } ;
struct drm_file {struct etnaviv_file_private* driver_priv; } ;
struct drm_device {struct etnaviv_drm_private* dev_private; } ;

/* Variables and functions */
 size_t DRM_SCHED_PRIORITY_NORMAL ; 
 int ENOMEM ; 
 int ETNA_MAX_PIPES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_sched_entity_init (int /*<<< orphan*/ *,struct drm_sched_rq**,int,int /*<<< orphan*/ *) ; 
 struct etnaviv_file_private* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etnaviv_open(struct drm_device *dev, struct drm_file *file)
{
	struct etnaviv_drm_private *priv = dev->dev_private;
	struct etnaviv_file_private *ctx;
	int i;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	for (i = 0; i < ETNA_MAX_PIPES; i++) {
		struct etnaviv_gpu *gpu = priv->gpu[i];
		struct drm_sched_rq *rq;

		if (gpu) {
			rq = &gpu->sched.sched_rq[DRM_SCHED_PRIORITY_NORMAL];
			drm_sched_entity_init(&ctx->sched_entity[i],
					      &rq, 1, NULL);
			}
	}

	file->driver_priv = ctx;

	return 0;
}