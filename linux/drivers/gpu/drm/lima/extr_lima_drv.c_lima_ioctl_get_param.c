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
struct lima_device {int /*<<< orphan*/  pp_version; int /*<<< orphan*/  gp_version; TYPE_1__* pipe; int /*<<< orphan*/  id; } ;
struct drm_lima_get_param {int param; int /*<<< orphan*/  value; scalar_t__ pad; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_processor; } ;

/* Variables and functions */
#define  DRM_LIMA_PARAM_GPU_ID 133 
 int /*<<< orphan*/  DRM_LIMA_PARAM_GPU_ID_MALI400 ; 
 int /*<<< orphan*/  DRM_LIMA_PARAM_GPU_ID_MALI450 ; 
 int /*<<< orphan*/  DRM_LIMA_PARAM_GPU_ID_UNKNOWN ; 
#define  DRM_LIMA_PARAM_GP_VERSION 132 
#define  DRM_LIMA_PARAM_NUM_PP 131 
#define  DRM_LIMA_PARAM_PP_VERSION 130 
 int EINVAL ; 
#define  lima_gpu_mali400 129 
#define  lima_gpu_mali450 128 
 size_t lima_pipe_pp ; 
 struct lima_device* to_lima_dev (struct drm_device*) ; 

__attribute__((used)) static int lima_ioctl_get_param(struct drm_device *dev, void *data, struct drm_file *file)
{
	struct drm_lima_get_param *args = data;
	struct lima_device *ldev = to_lima_dev(dev);

	if (args->pad)
		return -EINVAL;

	switch (args->param) {
	case DRM_LIMA_PARAM_GPU_ID:
		switch (ldev->id) {
		case lima_gpu_mali400:
			args->value = DRM_LIMA_PARAM_GPU_ID_MALI400;
			break;
		case lima_gpu_mali450:
			args->value = DRM_LIMA_PARAM_GPU_ID_MALI450;
			break;
		default:
			args->value = DRM_LIMA_PARAM_GPU_ID_UNKNOWN;
			break;
		}
		break;

	case DRM_LIMA_PARAM_NUM_PP:
		args->value = ldev->pipe[lima_pipe_pp].num_processor;
		break;

	case DRM_LIMA_PARAM_GP_VERSION:
		args->value = ldev->gp_version;
		break;

	case DRM_LIMA_PARAM_PP_VERSION:
		args->value = ldev->pp_version;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}