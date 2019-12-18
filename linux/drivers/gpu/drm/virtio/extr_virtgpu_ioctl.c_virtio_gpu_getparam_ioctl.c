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
struct virtio_gpu_device {int has_virgl_3d; } ;
struct drm_virtgpu_getparam {int param; int /*<<< orphan*/  value; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  VIRTGPU_PARAM_3D_FEATURES 129 
#define  VIRTGPU_PARAM_CAPSET_QUERY_FIX 128 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_gpu_getparam_ioctl(struct drm_device *dev, void *data,
				     struct drm_file *file_priv)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct drm_virtgpu_getparam *param = data;
	int value;

	switch (param->param) {
	case VIRTGPU_PARAM_3D_FEATURES:
		value = vgdev->has_virgl_3d == true ? 1 : 0;
		break;
	case VIRTGPU_PARAM_CAPSET_QUERY_FIX:
		value = 1;
		break;
	default:
		return -EINVAL;
	}
	if (copy_to_user(u64_to_user_ptr(param->value), &value, sizeof(int)))
		return -EFAULT;

	return 0;
}