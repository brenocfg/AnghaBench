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
typedef  int uint32_t ;
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_MEM_CNTL ; 
 int RADEON_MM_APER ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_IDX (int) ; 
 int RV100_HALF_MODE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_IDX (int,int) ; 

__attribute__((used)) static uint32_t combios_detect_ram(struct drm_device *dev, int ram,
				   int mem_addr_mapping)
{
	struct radeon_device *rdev = dev->dev_private;
	uint32_t mem_cntl;
	uint32_t mem_size;
	uint32_t addr = 0;

	mem_cntl = RREG32(RADEON_MEM_CNTL);
	if (mem_cntl & RV100_HALF_MODE)
		ram /= 2;
	mem_size = ram;
	mem_cntl &= ~(0xff << 8);
	mem_cntl |= (mem_addr_mapping & 0xff) << 8;
	WREG32(RADEON_MEM_CNTL, mem_cntl);
	RREG32(RADEON_MEM_CNTL);

	/* sdram reset ? */

	/* something like this????  */
	while (ram--) {
		addr = ram * 1024 * 1024;
		/* write to each page */
		WREG32_IDX((addr) | RADEON_MM_APER, 0xdeadbeef);
		/* read back and verify */
		if (RREG32_IDX((addr) | RADEON_MM_APER) != 0xdeadbeef)
			return 0;
	}

	return mem_size;
}