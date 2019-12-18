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
struct ras_common_if {int /*<<< orphan*/  block; } ;
struct amdgpu_ras {int flags; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int AMDGPU_RAS_FLAG_INIT_BY_VBIOS ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int __amdgpu_ras_feature_enable (struct amdgpu_device*,struct ras_common_if*,int) ; 
 int amdgpu_ras_feature_enable (struct amdgpu_device*,struct ras_common_if*,int) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ras_block_str (int /*<<< orphan*/ ) ; 

int amdgpu_ras_feature_enable_on_boot(struct amdgpu_device *adev,
		struct ras_common_if *head, bool enable)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);
	int ret;

	if (!con)
		return -EINVAL;

	if (con->flags & AMDGPU_RAS_FLAG_INIT_BY_VBIOS) {
		if (enable) {
			/* There is no harm to issue a ras TA cmd regardless of
			 * the currecnt ras state.
			 * If current state == target state, it will do nothing
			 * But sometimes it requests driver to reset and repost
			 * with error code -EAGAIN.
			 */
			ret = amdgpu_ras_feature_enable(adev, head, 1);
			/* With old ras TA, we might fail to enable ras.
			 * Log it and just setup the object.
			 * TODO need remove this WA in the future.
			 */
			if (ret == -EINVAL) {
				ret = __amdgpu_ras_feature_enable(adev, head, 1);
				if (!ret)
					DRM_INFO("RAS INFO: %s setup object\n",
						ras_block_str(head->block));
			}
		} else {
			/* setup the object then issue a ras TA disable cmd.*/
			ret = __amdgpu_ras_feature_enable(adev, head, 1);
			if (ret)
				return ret;

			ret = amdgpu_ras_feature_enable(adev, head, 0);
		}
	} else
		ret = amdgpu_ras_feature_enable(adev, head, enable);

	return ret;
}