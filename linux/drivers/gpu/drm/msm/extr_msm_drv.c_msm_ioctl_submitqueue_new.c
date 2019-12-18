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
struct drm_msm_submitqueue {int flags; int /*<<< orphan*/  id; int /*<<< orphan*/  prio; } ;
struct drm_file {int /*<<< orphan*/  driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MSM_SUBMITQUEUE_FLAGS ; 
 int msm_submitqueue_create (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_ioctl_submitqueue_new(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	struct drm_msm_submitqueue *args = data;

	if (args->flags & ~MSM_SUBMITQUEUE_FLAGS)
		return -EINVAL;

	return msm_submitqueue_create(dev, file->driver_priv, args->prio,
		args->flags, &args->id);
}