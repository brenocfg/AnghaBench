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
typedef  int uint16_t ;
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CLK_PWRMGT_CNTL ; 
 int RADEON_MC_BUSY ; 
 int RADEON_MC_IDLE ; 
 int RADEON_MC_STATUS ; 
 int RBIOS16 (int) ; 
 int RBIOS32 (int) ; 
 int RREG32 (int) ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void combios_parse_mmio_table(struct drm_device *dev, uint16_t offset)
{
	struct radeon_device *rdev = dev->dev_private;

	if (offset) {
		while (RBIOS16(offset)) {
			uint16_t cmd = ((RBIOS16(offset) & 0xe000) >> 13);
			uint32_t addr = (RBIOS16(offset) & 0x1fff);
			uint32_t val, and_mask, or_mask;
			uint32_t tmp;

			offset += 2;
			switch (cmd) {
			case 0:
				val = RBIOS32(offset);
				offset += 4;
				WREG32(addr, val);
				break;
			case 1:
				val = RBIOS32(offset);
				offset += 4;
				WREG32(addr, val);
				break;
			case 2:
				and_mask = RBIOS32(offset);
				offset += 4;
				or_mask = RBIOS32(offset);
				offset += 4;
				tmp = RREG32(addr);
				tmp &= and_mask;
				tmp |= or_mask;
				WREG32(addr, tmp);
				break;
			case 3:
				and_mask = RBIOS32(offset);
				offset += 4;
				or_mask = RBIOS32(offset);
				offset += 4;
				tmp = RREG32(addr);
				tmp &= and_mask;
				tmp |= or_mask;
				WREG32(addr, tmp);
				break;
			case 4:
				val = RBIOS16(offset);
				offset += 2;
				udelay(val);
				break;
			case 5:
				val = RBIOS16(offset);
				offset += 2;
				switch (addr) {
				case 8:
					while (val--) {
						if (!
						    (RREG32_PLL
						     (RADEON_CLK_PWRMGT_CNTL) &
						     RADEON_MC_BUSY))
							break;
					}
					break;
				case 9:
					while (val--) {
						if ((RREG32(RADEON_MC_STATUS) &
						     RADEON_MC_IDLE))
							break;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}