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
struct v3d_file_priv {int /*<<< orphan*/ * sched_entity; struct v3d_dev* v3d; } ;
struct v3d_dev {TYPE_2__* queue; } ;
struct drm_sched_rq {int dummy; } ;
struct drm_file {struct v3d_file_priv* driver_priv; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {struct drm_sched_rq* sched_rq; } ;
struct TYPE_4__ {TYPE_1__ sched; } ;

/* Variables and functions */
 size_t DRM_SCHED_PRIORITY_NORMAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int V3D_MAX_QUEUES ; 
 int /*<<< orphan*/  drm_sched_entity_init (int /*<<< orphan*/ *,struct drm_sched_rq**,int,int /*<<< orphan*/ *) ; 
 struct v3d_file_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 

__attribute__((used)) static int
v3d_open(struct drm_device *dev, struct drm_file *file)
{
	struct v3d_dev *v3d = to_v3d_dev(dev);
	struct v3d_file_priv *v3d_priv;
	struct drm_sched_rq *rq;
	int i;

	v3d_priv = kzalloc(sizeof(*v3d_priv), GFP_KERNEL);
	if (!v3d_priv)
		return -ENOMEM;

	v3d_priv->v3d = v3d;

	for (i = 0; i < V3D_MAX_QUEUES; i++) {
		rq = &v3d->queue[i].sched.sched_rq[DRM_SCHED_PRIORITY_NORMAL];
		drm_sched_entity_init(&v3d_priv->sched_entity[i], &rq, 1, NULL);
	}

	file->driver_priv = v3d_priv;

	return 0;
}