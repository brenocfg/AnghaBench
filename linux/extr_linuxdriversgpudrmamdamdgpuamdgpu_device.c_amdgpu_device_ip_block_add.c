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
struct amdgpu_ip_block_version {TYPE_1__* funcs; } ;
struct amdgpu_device {int /*<<< orphan*/  num_ip_blocks; TYPE_2__* ip_blocks; } ;
struct TYPE_4__ {struct amdgpu_ip_block_version const* version; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 

int amdgpu_device_ip_block_add(struct amdgpu_device *adev,
			       const struct amdgpu_ip_block_version *ip_block_version)
{
	if (!ip_block_version)
		return -EINVAL;

	DRM_INFO("add ip block number %d <%s>\n", adev->num_ip_blocks,
		  ip_block_version->funcs->name);

	adev->ip_blocks[adev->num_ip_blocks++].version = ip_block_version;

	return 0;
}