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
typedef  scalar_t__ u32 ;
struct amdgpu_ip_block {TYPE_1__* version; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amd_ip_block_type { ____Placeholder_amd_ip_block_type } amd_ip_block_type ;
struct TYPE_2__ {scalar_t__ major; scalar_t__ minor; } ;

/* Variables and functions */
 struct amdgpu_ip_block* amdgpu_device_ip_get_ip_block (struct amdgpu_device*,int) ; 

int amdgpu_device_ip_block_version_cmp(struct amdgpu_device *adev,
				       enum amd_ip_block_type type,
				       u32 major, u32 minor)
{
	struct amdgpu_ip_block *ip_block = amdgpu_device_ip_get_ip_block(adev, type);

	if (ip_block && ((ip_block->version->major > major) ||
			((ip_block->version->major == major) &&
			(ip_block->version->minor >= minor))))
		return 0;

	return 1;
}