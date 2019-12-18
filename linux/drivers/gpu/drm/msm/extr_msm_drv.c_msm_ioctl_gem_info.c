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
struct msm_gem_object {char* name; } ;
struct drm_msm_gem_info {int info; int len; int /*<<< orphan*/  value; int /*<<< orphan*/  handle; scalar_t__ pad; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
#define  MSM_INFO_GET_IOVA 131 
#define  MSM_INFO_GET_NAME 130 
#define  MSM_INFO_GET_OFFSET 129 
#define  MSM_INFO_SET_NAME 128 
 int /*<<< orphan*/  copy_from_user (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ ,char*,int) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  isprint (char) ; 
 int /*<<< orphan*/  msm_gem_mmap_offset (struct drm_gem_object*) ; 
 int msm_ioctl_gem_info_iova (struct drm_device*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_ioctl_gem_info(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	struct drm_msm_gem_info *args = data;
	struct drm_gem_object *obj;
	struct msm_gem_object *msm_obj;
	int i, ret = 0;

	if (args->pad)
		return -EINVAL;

	switch (args->info) {
	case MSM_INFO_GET_OFFSET:
	case MSM_INFO_GET_IOVA:
		/* value returned as immediate, not pointer, so len==0: */
		if (args->len)
			return -EINVAL;
		break;
	case MSM_INFO_SET_NAME:
	case MSM_INFO_GET_NAME:
		break;
	default:
		return -EINVAL;
	}

	obj = drm_gem_object_lookup(file, args->handle);
	if (!obj)
		return -ENOENT;

	msm_obj = to_msm_bo(obj);

	switch (args->info) {
	case MSM_INFO_GET_OFFSET:
		args->value = msm_gem_mmap_offset(obj);
		break;
	case MSM_INFO_GET_IOVA:
		ret = msm_ioctl_gem_info_iova(dev, obj, &args->value);
		break;
	case MSM_INFO_SET_NAME:
		/* length check should leave room for terminating null: */
		if (args->len >= sizeof(msm_obj->name)) {
			ret = -EINVAL;
			break;
		}
		if (copy_from_user(msm_obj->name, u64_to_user_ptr(args->value),
				   args->len)) {
			msm_obj->name[0] = '\0';
			ret = -EFAULT;
			break;
		}
		msm_obj->name[args->len] = '\0';
		for (i = 0; i < args->len; i++) {
			if (!isprint(msm_obj->name[i])) {
				msm_obj->name[i] = '\0';
				break;
			}
		}
		break;
	case MSM_INFO_GET_NAME:
		if (args->value && (args->len < strlen(msm_obj->name))) {
			ret = -EINVAL;
			break;
		}
		args->len = strlen(msm_obj->name);
		if (args->value) {
			if (copy_to_user(u64_to_user_ptr(args->value),
					 msm_obj->name, args->len))
				ret = -EFAULT;
		}
		break;
	}

	drm_gem_object_put_unlocked(obj);

	return ret;
}