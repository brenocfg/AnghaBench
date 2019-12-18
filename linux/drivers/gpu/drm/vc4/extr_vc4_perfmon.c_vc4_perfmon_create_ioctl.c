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
struct vc4_perfmon {scalar_t__* events; unsigned int ncounters; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  idr; } ;
struct vc4_file {TYPE_1__ perfmon; } ;
struct vc4_dev {int /*<<< orphan*/  v3d; } ;
struct drm_vc4_perfmon_create {unsigned int ncounters; scalar_t__* events; int id; } ;
struct drm_file {struct vc4_file* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 unsigned int DRM_VC4_MAX_PERF_COUNTERS ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VC4_PERFCNT_NUM_EVENTS ; 
 int /*<<< orphan*/  VC4_PERFMONID_MAX ; 
 int /*<<< orphan*/  VC4_PERFMONID_MIN ; 
 int /*<<< orphan*/  counters ; 
 int idr_alloc (int /*<<< orphan*/ *,struct vc4_perfmon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vc4_perfmon*) ; 
 struct vc4_perfmon* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  struct_size (struct vc4_perfmon*,int /*<<< orphan*/ ,unsigned int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

int vc4_perfmon_create_ioctl(struct drm_device *dev, void *data,
			     struct drm_file *file_priv)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_file *vc4file = file_priv->driver_priv;
	struct drm_vc4_perfmon_create *req = data;
	struct vc4_perfmon *perfmon;
	unsigned int i;
	int ret;

	if (!vc4->v3d) {
		DRM_DEBUG("Creating perfmon no VC4 V3D probed\n");
		return -ENODEV;
	}

	/* Number of monitored counters cannot exceed HW limits. */
	if (req->ncounters > DRM_VC4_MAX_PERF_COUNTERS ||
	    !req->ncounters)
		return -EINVAL;

	/* Make sure all events are valid. */
	for (i = 0; i < req->ncounters; i++) {
		if (req->events[i] >= VC4_PERFCNT_NUM_EVENTS)
			return -EINVAL;
	}

	perfmon = kzalloc(struct_size(perfmon, counters, req->ncounters),
			  GFP_KERNEL);
	if (!perfmon)
		return -ENOMEM;

	for (i = 0; i < req->ncounters; i++)
		perfmon->events[i] = req->events[i];

	perfmon->ncounters = req->ncounters;

	refcount_set(&perfmon->refcnt, 1);

	mutex_lock(&vc4file->perfmon.lock);
	ret = idr_alloc(&vc4file->perfmon.idr, perfmon, VC4_PERFMONID_MIN,
			VC4_PERFMONID_MAX, GFP_KERNEL);
	mutex_unlock(&vc4file->perfmon.lock);

	if (ret < 0) {
		kfree(perfmon);
		return ret;
	}

	req->id = ret;
	return 0;
}