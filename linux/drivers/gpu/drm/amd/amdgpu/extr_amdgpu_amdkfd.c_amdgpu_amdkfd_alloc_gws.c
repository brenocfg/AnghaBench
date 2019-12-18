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
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;
struct amdgpu_bo_param {size_t size; int byte_align; int /*<<< orphan*/ * resv; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  domain; } ;
struct amdgpu_bo {int dummy; } ;
typedef  int /*<<< orphan*/  bp ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_NO_CPU_ACCESS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GWS ; 
 int amdgpu_bo_create (struct amdgpu_device*,struct amdgpu_bo_param*,struct amdgpu_bo**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 

int amdgpu_amdkfd_alloc_gws(struct kgd_dev *kgd, size_t size,
				void **mem_obj)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;
	struct amdgpu_bo *bo = NULL;
	struct amdgpu_bo_param bp;
	int r;

	memset(&bp, 0, sizeof(bp));
	bp.size = size;
	bp.byte_align = 1;
	bp.domain = AMDGPU_GEM_DOMAIN_GWS;
	bp.flags = AMDGPU_GEM_CREATE_NO_CPU_ACCESS;
	bp.type = ttm_bo_type_device;
	bp.resv = NULL;

	r = amdgpu_bo_create(adev, &bp, &bo);
	if (r) {
		dev_err(adev->dev,
			"failed to allocate gws BO for amdkfd (%d)\n", r);
		return r;
	}

	*mem_obj = bo;
	return 0;
}