#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int hw; int /*<<< orphan*/  valid; } ;
struct amdgpu_ip_block {TYPE_3__ status; TYPE_2__* version; } ;
struct amdgpu_device {int num_ip_blocks; struct amdgpu_ip_block* ip_blocks; } ;
typedef  enum amd_ip_block_type { ____Placeholder_amd_ip_block_type } amd_ip_block_type ;
struct TYPE_5__ {int type; TYPE_1__* funcs; } ;
struct TYPE_4__ {int (* hw_init ) (struct amdgpu_device*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  AMD_IP_BLOCK_TYPE_DCE 133 
#define  AMD_IP_BLOCK_TYPE_GFX 132 
#define  AMD_IP_BLOCK_TYPE_SDMA 131 
#define  AMD_IP_BLOCK_TYPE_SMC 130 
#define  AMD_IP_BLOCK_TYPE_UVD 129 
#define  AMD_IP_BLOCK_TYPE_VCE 128 
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int amdgpu_device_ip_reinit_late_sriov(struct amdgpu_device *adev)
{
	int i, r;

	static enum amd_ip_block_type ip_order[] = {
		AMD_IP_BLOCK_TYPE_SMC,
		AMD_IP_BLOCK_TYPE_DCE,
		AMD_IP_BLOCK_TYPE_GFX,
		AMD_IP_BLOCK_TYPE_SDMA,
		AMD_IP_BLOCK_TYPE_UVD,
		AMD_IP_BLOCK_TYPE_VCE
	};

	for (i = 0; i < ARRAY_SIZE(ip_order); i++) {
		int j;
		struct amdgpu_ip_block *block;

		for (j = 0; j < adev->num_ip_blocks; j++) {
			block = &adev->ip_blocks[j];

			if (block->version->type != ip_order[i] ||
				!block->status.valid ||
				block->status.hw)
				continue;

			r = block->version->funcs->hw_init(adev);
			DRM_INFO("RE-INIT-late: %s %s\n", block->version->funcs->name, r?"failed":"succeeded");
			if (r)
				return r;
			block->status.hw = true;
		}
	}

	return 0;
}