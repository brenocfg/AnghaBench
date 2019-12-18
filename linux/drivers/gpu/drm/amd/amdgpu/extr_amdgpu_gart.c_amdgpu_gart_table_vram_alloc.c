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
struct TYPE_2__ {int /*<<< orphan*/ * bo; int /*<<< orphan*/  table_size; } ;
struct amdgpu_device {TYPE_1__ gart; } ;
struct amdgpu_bo_param {int flags; int /*<<< orphan*/ * resv; int /*<<< orphan*/  type; int /*<<< orphan*/  domain; int /*<<< orphan*/  byte_align; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  bp ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create (struct amdgpu_device*,struct amdgpu_bo_param*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 

int amdgpu_gart_table_vram_alloc(struct amdgpu_device *adev)
{
	int r;

	if (adev->gart.bo == NULL) {
		struct amdgpu_bo_param bp;

		memset(&bp, 0, sizeof(bp));
		bp.size = adev->gart.table_size;
		bp.byte_align = PAGE_SIZE;
		bp.domain = AMDGPU_GEM_DOMAIN_VRAM;
		bp.flags = AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED |
			AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
		bp.type = ttm_bo_type_kernel;
		bp.resv = NULL;
		r = amdgpu_bo_create(adev, &bp, &adev->gart.bo);
		if (r) {
			return r;
		}
	}
	return 0;
}