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
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 int R300_MEM_PWRUP_COMPLETE ; 
 int RADEON_B3MEM_RESET_MASK ; 
 int RADEON_MEM_PWRUP_COMPLETE ; 
 int /*<<< orphan*/  RADEON_MEM_SDRAM_MODE_REG ; 
 int /*<<< orphan*/  RADEON_MEM_STR_CNTL ; 
 int RADEON_SDRAM_MODE_MASK ; 
 int RBIOS16 (scalar_t__) ; 
 int RBIOS8 (scalar_t__) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void combios_parse_ram_reset_table(struct drm_device *dev,
					  uint16_t offset)
{
	struct radeon_device *rdev = dev->dev_private;
	uint32_t tmp;

	if (offset) {
		uint8_t val = RBIOS8(offset);
		while (val != 0xff) {
			offset++;

			if (val == 0x0f) {
				uint32_t channel_complete_mask;

				if (ASIC_IS_R300(rdev))
					channel_complete_mask =
					    R300_MEM_PWRUP_COMPLETE;
				else
					channel_complete_mask =
					    RADEON_MEM_PWRUP_COMPLETE;
				tmp = 20000;
				while (tmp--) {
					if ((RREG32(RADEON_MEM_STR_CNTL) &
					     channel_complete_mask) ==
					    channel_complete_mask)
						break;
				}
			} else {
				uint32_t or_mask = RBIOS16(offset);
				offset += 2;

				tmp = RREG32(RADEON_MEM_SDRAM_MODE_REG);
				tmp &= RADEON_SDRAM_MODE_MASK;
				tmp |= or_mask;
				WREG32(RADEON_MEM_SDRAM_MODE_REG, tmp);

				or_mask = val << 24;
				tmp = RREG32(RADEON_MEM_SDRAM_MODE_REG);
				tmp &= RADEON_B3MEM_RESET_MASK;
				tmp |= or_mask;
				WREG32(RADEON_MEM_SDRAM_MODE_REG, tmp);
			}
			val = RBIOS8(offset);
		}
	}
}