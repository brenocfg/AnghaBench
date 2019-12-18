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
typedef  int /*<<< orphan*/  uint8_t ;
struct kgd_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  physical_node_id; } ;
struct TYPE_4__ {TYPE_1__ xgmi; } ;
struct amdgpu_device {TYPE_2__ gmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int amdgpu_xgmi_get_hops_count (struct amdgpu_device*,struct amdgpu_device*) ; 

uint8_t amdgpu_amdkfd_get_xgmi_hops_count(struct kgd_dev *dst, struct kgd_dev *src)
{
	struct amdgpu_device *peer_adev = (struct amdgpu_device *)src;
	struct amdgpu_device *adev = (struct amdgpu_device *)dst;
	int ret = amdgpu_xgmi_get_hops_count(adev, peer_adev);

	if (ret < 0) {
		DRM_ERROR("amdgpu: failed to get  xgmi hops count between node %d and %d. ret = %d\n",
			adev->gmc.xgmi.physical_node_id,
			peer_adev->gmc.xgmi.physical_node_id, ret);
		ret = 0;
	}
	return  (uint8_t)ret;
}