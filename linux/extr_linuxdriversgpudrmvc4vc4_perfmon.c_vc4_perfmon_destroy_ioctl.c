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
struct vc4_perfmon {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  idr; } ;
struct vc4_file {TYPE_1__ perfmon; } ;
struct drm_vc4_perfmon_destroy {int /*<<< orphan*/  id; } ;
struct drm_file {struct vc4_file* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vc4_perfmon* idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_perfmon_put (struct vc4_perfmon*) ; 

int vc4_perfmon_destroy_ioctl(struct drm_device *dev, void *data,
			      struct drm_file *file_priv)
{
	struct vc4_file *vc4file = file_priv->driver_priv;
	struct drm_vc4_perfmon_destroy *req = data;
	struct vc4_perfmon *perfmon;

	mutex_lock(&vc4file->perfmon.lock);
	perfmon = idr_remove(&vc4file->perfmon.idr, req->id);
	mutex_unlock(&vc4file->perfmon.lock);

	if (!perfmon)
		return -EINVAL;

	vc4_perfmon_put(perfmon);
	return 0;
}