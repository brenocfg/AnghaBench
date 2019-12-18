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
struct TYPE_4__ {int gpu_addr; int max_handles; } ;
struct radeon_device {int family; TYPE_2__ uvd; TYPE_1__* uvd_fw; } ;
struct TYPE_3__ {scalar_t__ size; } ;

/* Variables and functions */
#define  CHIP_ARUBA 147 
#define  CHIP_BARTS 146 
#define  CHIP_CAICOS 145 
#define  CHIP_CAYMAN 144 
#define  CHIP_CEDAR 143 
#define  CHIP_CYPRESS 142 
#define  CHIP_HEMLOCK 141 
#define  CHIP_JUNIPER 140 
#define  CHIP_OLAND 139 
#define  CHIP_PALM 138 
#define  CHIP_PITCAIRN 137 
#define  CHIP_REDWOOD 136 
#define  CHIP_RV710 135 
#define  CHIP_RV730 134 
#define  CHIP_RV740 133 
 int CHIP_RV770 ; 
#define  CHIP_SUMO 132 
#define  CHIP_SUMO2 131 
#define  CHIP_TAHITI 130 
#define  CHIP_TURKS 129 
#define  CHIP_VERDE 128 
 int EINVAL ; 
 int RADEON_GPU_PAGE_ALIGN (scalar_t__) ; 
 int RADEON_UVD_HEAP_SIZE ; 
 int RADEON_UVD_SESSION_SIZE ; 
 int RADEON_UVD_STACK_SIZE ; 
 int /*<<< orphan*/  UVD_LMI_ADDR_EXT ; 
 int /*<<< orphan*/  UVD_LMI_EXT40_ADDR ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  UVD_VCPU_CACHE_SIZE2 ; 
 int /*<<< orphan*/  UVD_VCPU_CHIP_ID ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int radeon_uvd_resume (struct radeon_device*) ; 
 int uvd_v1_0_resume (struct radeon_device*) ; 

int uvd_v2_2_resume(struct radeon_device *rdev)
{
	uint64_t addr;
	uint32_t chip_id, size;
	int r;

	/* RV770 uses V1.0 MC */
	if (rdev->family == CHIP_RV770)
		return uvd_v1_0_resume(rdev);

	r = radeon_uvd_resume(rdev);
	if (r)
		return r;

	/* programm the VCPU memory controller bits 0-27 */
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

	/* tell firmware which hardware it is running on */
	switch (rdev->family) {
	default:
		return -EINVAL;
	case CHIP_RV710:
		chip_id = 0x01000005;
		break;
	case CHIP_RV730:
		chip_id = 0x01000006;
		break;
	case CHIP_RV740:
		chip_id = 0x01000007;
		break;
	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
		chip_id = 0x01000008;
		break;
	case CHIP_JUNIPER:
		chip_id = 0x01000009;
		break;
	case CHIP_REDWOOD:
		chip_id = 0x0100000a;
		break;
	case CHIP_CEDAR:
		chip_id = 0x0100000b;
		break;
	case CHIP_SUMO:
	case CHIP_SUMO2:
		chip_id = 0x0100000c;
		break;
	case CHIP_PALM:
		chip_id = 0x0100000e;
		break;
	case CHIP_CAYMAN:
		chip_id = 0x0100000f;
		break;
	case CHIP_BARTS:
		chip_id = 0x01000010;
		break;
	case CHIP_TURKS:
		chip_id = 0x01000011;
		break;
	case CHIP_CAICOS:
		chip_id = 0x01000012;
		break;
	case CHIP_TAHITI:
		chip_id = 0x01000014;
		break;
	case CHIP_VERDE:
		chip_id = 0x01000015;
		break;
	case CHIP_PITCAIRN:
	case CHIP_OLAND:
		chip_id = 0x01000016;
		break;
	case CHIP_ARUBA:
		chip_id = 0x01000017;
		break;
	}
	WREG32(UVD_VCPU_CHIP_ID, chip_id);

	return 0;
}