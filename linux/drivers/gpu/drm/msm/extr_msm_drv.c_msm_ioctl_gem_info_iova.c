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
typedef  int /*<<< orphan*/  uint64_t ;
struct msm_drm_private {TYPE_1__* gpu; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  aspace; } ;

/* Variables and functions */
 int EINVAL ; 
 int msm_gem_get_iova (struct drm_gem_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_ioctl_gem_info_iova(struct drm_device *dev,
		struct drm_gem_object *obj, uint64_t *iova)
{
	struct msm_drm_private *priv = dev->dev_private;

	if (!priv->gpu)
		return -EINVAL;

	/*
	 * Don't pin the memory here - just get an address so that userspace can
	 * be productive
	 */
	return msm_gem_get_iova(obj, priv->gpu->aspace, iova);
}