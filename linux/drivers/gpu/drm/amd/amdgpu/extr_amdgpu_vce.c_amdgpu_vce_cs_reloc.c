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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct amdgpu_cs_parser {int dummy; } ;
struct amdgpu_bo_va_mapping {int last; int start; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_SIZE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int,int,...) ; 
 int EINVAL ; 
 scalar_t__ amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int amdgpu_cs_find_mapping (struct amdgpu_cs_parser*,int,struct amdgpu_bo**,struct amdgpu_bo_va_mapping**) ; 
 scalar_t__ amdgpu_get_ib_value (struct amdgpu_cs_parser*,int,int) ; 
 int /*<<< orphan*/  amdgpu_set_ib_value (struct amdgpu_cs_parser*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static int amdgpu_vce_cs_reloc(struct amdgpu_cs_parser *p, uint32_t ib_idx,
			       int lo, int hi, unsigned size, uint32_t index)
{
	struct amdgpu_bo_va_mapping *mapping;
	struct amdgpu_bo *bo;
	uint64_t addr;
	int r;

	if (index == 0xffffffff)
		index = 0;

	addr = ((uint64_t)amdgpu_get_ib_value(p, ib_idx, lo)) |
	       ((uint64_t)amdgpu_get_ib_value(p, ib_idx, hi)) << 32;
	addr += ((uint64_t)size) * ((uint64_t)index);

	r = amdgpu_cs_find_mapping(p, addr, &bo, &mapping);
	if (r) {
		DRM_ERROR("Can't find BO for addr 0x%010Lx %d %d %d %d\n",
			  addr, lo, hi, size, index);
		return r;
	}

	if ((addr + (uint64_t)size) >
	    (mapping->last + 1) * AMDGPU_GPU_PAGE_SIZE) {
		DRM_ERROR("BO to small for addr 0x%010Lx %d %d\n",
			  addr, lo, hi);
		return -EINVAL;
	}

	addr -= mapping->start * AMDGPU_GPU_PAGE_SIZE;
	addr += amdgpu_bo_gpu_offset(bo);
	addr -= ((uint64_t)size) * ((uint64_t)index);

	amdgpu_set_ib_value(p, ib_idx, lo, lower_32_bits(addr));
	amdgpu_set_ib_value(p, ib_idx, hi, upper_32_bits(addr));

	return 0;
}