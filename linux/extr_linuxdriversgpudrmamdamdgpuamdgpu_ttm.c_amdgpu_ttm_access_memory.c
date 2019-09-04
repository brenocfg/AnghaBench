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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ mem_type; } ;
struct ttm_buffer_object {TYPE_1__ mem; } ;
struct drm_mm_node {unsigned long start; int size; } ;
struct TYPE_6__ {int mc_vram_size; } ;
struct amdgpu_device {int /*<<< orphan*/  mmio_idx_lock; TYPE_3__ gmc; } ;
struct TYPE_5__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {TYPE_2__ tbo; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long PAGE_SHIFT ; 
 int RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  WREG32_NO_KIQ (int /*<<< orphan*/ ,int) ; 
 struct drm_mm_node* amdgpu_find_mm_node (int /*<<< orphan*/ *,unsigned long*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int /*<<< orphan*/  mmMM_DATA ; 
 int /*<<< orphan*/  mmMM_INDEX ; 
 int /*<<< orphan*/  mmMM_INDEX_HI ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 

__attribute__((used)) static int amdgpu_ttm_access_memory(struct ttm_buffer_object *bo,
				    unsigned long offset,
				    void *buf, int len, int write)
{
	struct amdgpu_bo *abo = ttm_to_amdgpu_bo(bo);
	struct amdgpu_device *adev = amdgpu_ttm_adev(abo->tbo.bdev);
	struct drm_mm_node *nodes;
	uint32_t value = 0;
	int ret = 0;
	uint64_t pos;
	unsigned long flags;

	if (bo->mem.mem_type != TTM_PL_VRAM)
		return -EIO;

	nodes = amdgpu_find_mm_node(&abo->tbo.mem, &offset);
	pos = (nodes->start << PAGE_SHIFT) + offset;

	while (len && pos < adev->gmc.mc_vram_size) {
		uint64_t aligned_pos = pos & ~(uint64_t)3;
		uint32_t bytes = 4 - (pos & 3);
		uint32_t shift = (pos & 3) * 8;
		uint32_t mask = 0xffffffff << shift;

		if (len < bytes) {
			mask &= 0xffffffff >> (bytes - len) * 8;
			bytes = len;
		}

		spin_lock_irqsave(&adev->mmio_idx_lock, flags);
		WREG32_NO_KIQ(mmMM_INDEX, ((uint32_t)aligned_pos) | 0x80000000);
		WREG32_NO_KIQ(mmMM_INDEX_HI, aligned_pos >> 31);
		if (!write || mask != 0xffffffff)
			value = RREG32_NO_KIQ(mmMM_DATA);
		if (write) {
			value &= ~mask;
			value |= (*(uint32_t *)buf << shift) & mask;
			WREG32_NO_KIQ(mmMM_DATA, value);
		}
		spin_unlock_irqrestore(&adev->mmio_idx_lock, flags);
		if (!write) {
			value = (value & mask) >> shift;
			memcpy(buf, &value, bytes);
		}

		ret += bytes;
		buf = (uint8_t *)buf + bytes;
		pos += bytes;
		len -= bytes;
		if (pos >= (nodes->start + nodes->size) << PAGE_SHIFT) {
			++nodes;
			pos = (nodes->start << PAGE_SHIFT);
		}
	}

	return ret;
}