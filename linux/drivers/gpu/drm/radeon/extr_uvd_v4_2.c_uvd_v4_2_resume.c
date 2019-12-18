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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int gpu_addr; int max_handles; scalar_t__ fw_header_present; } ;
struct radeon_device {TYPE_2__ uvd; TYPE_1__* uvd_fw; } ;
struct TYPE_3__ {scalar_t__ size; } ;

/* Variables and functions */
 int RADEON_GPU_PAGE_ALIGN (scalar_t__) ; 
 int RADEON_UVD_HEAP_SIZE ; 
 int RADEON_UVD_SESSION_SIZE ; 
 int RADEON_UVD_STACK_SIZE ; 
 int /*<<< orphan*/  UVD_GP_SCRATCH4 ; 
 int /*<<< orphan*/  UVD_LMI_ADDR_EXT ; 
 int /*<<< orphan*/  UVD_LMI_EXT40_ADDR ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_SIZE2 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

int uvd_v4_2_resume(struct radeon_device *rdev)
{
	uint64_t addr;
	uint32_t size;

	/* programm the VCPU memory controller bits 0-27 */

	/* skip over the header of the new firmware format */
	if (rdev->uvd.fw_header_present)
		addr = (rdev->uvd.gpu_addr + 0x200) >> 3;
	else
		addr = rdev->uvd.gpu_addr >> 3;

	size = RADEON_GPU_PAGE_ALIGN(rdev->uvd_fw->size + 4) >> 3;
	WREG32(UVD_VCPU_CACHE_OFFSET0, addr);
	WREG32(UVD_VCPU_CACHE_SIZE0, size);

	addr += size;
	size = RADEON_UVD_HEAP_SIZE >> 3;
	WREG32(UVD_VCPU_CACHE_OFFSET1, addr);
	WREG32(UVD_VCPU_CACHE_SIZE1, size);

	addr += size;
	size = (RADEON_UVD_STACK_SIZE +
	       (RADEON_UVD_SESSION_SIZE * rdev->uvd.max_handles)) >> 3;
	WREG32(UVD_VCPU_CACHE_OFFSET2, addr);
	WREG32(UVD_VCPU_CACHE_SIZE2, size);

	/* bits 28-31 */
	addr = (rdev->uvd.gpu_addr >> 28) & 0xF;
	WREG32(UVD_LMI_ADDR_EXT, (addr << 12) | (addr << 0));

	/* bits 32-39 */
	addr = (rdev->uvd.gpu_addr >> 32) & 0xFF;
	WREG32(UVD_LMI_EXT40_ADDR, addr | (0x9 << 16) | (0x1 << 31));

	if (rdev->uvd.fw_header_present)
		WREG32(UVD_GP_SCRATCH4, rdev->uvd.max_handles);

	return 0;
}