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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct radeon_device {int flags; scalar_t__ family; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_RN50 (struct radeon_device*) ; 
 scalar_t__ CHIP_R200 ; 
 int /*<<< orphan*/  COMBIOS_DETECTED_MEM_TABLE ; 
 int /*<<< orphan*/  COMBIOS_MEM_CONFIG_TABLE ; 
 int /*<<< orphan*/  RADEON_CONFIG_MEMSIZE ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  RADEON_MEM_CNTL ; 
 int RBIOS16 (scalar_t__) ; 
 int RBIOS32 (scalar_t__) ; 
 int RBIOS8 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int combios_detect_ram (struct drm_device*,int,int) ; 
 scalar_t__ combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void combios_write_ram_size(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	uint8_t rev;
	uint16_t offset;
	uint32_t mem_size = 0;
	uint32_t mem_cntl = 0;

	/* should do something smarter here I guess... */
	if (rdev->flags & RADEON_IS_IGP)
		return;

	/* first check detected mem table */
	offset = combios_get_table_offset(dev, COMBIOS_DETECTED_MEM_TABLE);
	if (offset) {
		rev = RBIOS8(offset);
		if (rev < 3) {
			mem_cntl = RBIOS32(offset + 1);
			mem_size = RBIOS16(offset + 5);
			if ((rdev->family < CHIP_R200) &&
			    !ASIC_IS_RN50(rdev))
				WREG32(RADEON_MEM_CNTL, mem_cntl);
		}
	}

	if (!mem_size) {
		offset =
		    combios_get_table_offset(dev, COMBIOS_MEM_CONFIG_TABLE);
		if (offset) {
			rev = RBIOS8(offset - 1);
			if (rev < 1) {
				if ((rdev->family < CHIP_R200)
				    && !ASIC_IS_RN50(rdev)) {
					int ram = 0;
					int mem_addr_mapping = 0;

					while (RBIOS8(offset)) {
						ram = RBIOS8(offset);
						mem_addr_mapping =
						    RBIOS8(offset + 1);
						if (mem_addr_mapping != 0x25)
							ram *= 2;
						mem_size =
						    combios_detect_ram(dev, ram,
								       mem_addr_mapping);
						if (mem_size)
							break;
						offset += 2;
					}
				} else
					mem_size = RBIOS8(offset);
			} else {
				mem_size = RBIOS8(offset);
				mem_size *= 2;	/* convert to MB */
			}
		}
	}

	mem_size *= (1024 * 1024);	/* convert to bytes */
	WREG32(RADEON_CONFIG_MEMSIZE, mem_size);
}