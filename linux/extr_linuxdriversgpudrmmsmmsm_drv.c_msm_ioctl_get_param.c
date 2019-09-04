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
struct msm_gpu {TYPE_1__* funcs; } ;
struct msm_drm_private {struct msm_gpu* gpu; } ;
struct drm_msm_param {scalar_t__ pipe; int /*<<< orphan*/  value; int /*<<< orphan*/  param; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {int (* get_param ) (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ MSM_PIPE_3D0 ; 
 int stub1 (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_ioctl_get_param(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct drm_msm_param *args = data;
	struct msm_gpu *gpu;

	/* for now, we just have 3d pipe.. eventually this would need to
	 * be more clever to dispatch to appropriate gpu module:
	 */
	if (args->pipe != MSM_PIPE_3D0)
		return -EINVAL;

	gpu = priv->gpu;

	if (!gpu)
		return -ENXIO;

	return gpu->funcs->get_param(gpu, args->param, &args->value);
}