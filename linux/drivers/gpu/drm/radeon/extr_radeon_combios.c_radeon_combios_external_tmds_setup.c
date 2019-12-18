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
typedef  int uint16_t ;
struct radeon_encoder_ext_tmds {int slave_addr; int /*<<< orphan*/  i2c_bus; } ;
struct radeon_encoder {struct radeon_encoder_ext_tmds* enc_priv; } ;
struct radeon_device {int flags; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBIOS_EXT_TMDS_INFO_TABLE ; 
 int /*<<< orphan*/  COMBIOS_TMDS_POWER_ON_TABLE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int RADEON_IS_IGP ; 
 int RBIOS16 (int) ; 
 int RBIOS32 (int) ; 
 int RBIOS8 (int) ; 
 int RREG32 (int) ; 
 int RREG32_PLL (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  WREG32_PLL (int,int) ; 
 int combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  radeon_i2c_put_byte (int /*<<< orphan*/ ,int,int,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool radeon_combios_external_tmds_setup(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint16_t offset;
	uint8_t blocks, slave_addr, rev;
	uint32_t index, id;
	uint32_t reg, val, and_mask, or_mask;
	struct radeon_encoder_ext_tmds *tmds = radeon_encoder->enc_priv;

	if (!tmds)
		return false;

	if (rdev->flags & RADEON_IS_IGP) {
		offset = combios_get_table_offset(dev, COMBIOS_TMDS_POWER_ON_TABLE);
		rev = RBIOS8(offset);
		if (offset) {
			rev = RBIOS8(offset);
			if (rev > 1) {
				blocks = RBIOS8(offset + 3);
				index = offset + 4;
				while (blocks > 0) {
					id = RBIOS16(index);
					index += 2;
					switch (id >> 13) {
					case 0:
						reg = (id & 0x1fff) * 4;
						val = RBIOS32(index);
						index += 4;
						WREG32(reg, val);
						break;
					case 2:
						reg = (id & 0x1fff) * 4;
						and_mask = RBIOS32(index);
						index += 4;
						or_mask = RBIOS32(index);
						index += 4;
						val = RREG32(reg);
						val = (val & and_mask) | or_mask;
						WREG32(reg, val);
						break;
					case 3:
						val = RBIOS16(index);
						index += 2;
						udelay(val);
						break;
					case 4:
						val = RBIOS16(index);
						index += 2;
						mdelay(val);
						break;
					case 6:
						slave_addr = id & 0xff;
						slave_addr >>= 1; /* 7 bit addressing */
						index++;
						reg = RBIOS8(index);
						index++;
						val = RBIOS8(index);
						index++;
						radeon_i2c_put_byte(tmds->i2c_bus,
								    slave_addr,
								    reg, val);
						break;
					default:
						DRM_ERROR("Unknown id %d\n", id >> 13);
						break;
					}
					blocks--;
				}
				return true;
			}
		}
	} else {
		offset = combios_get_table_offset(dev, COMBIOS_EXT_TMDS_INFO_TABLE);
		if (offset) {
			index = offset + 10;
			id = RBIOS16(index);
			while (id != 0xffff) {
				index += 2;
				switch (id >> 13) {
				case 0:
					reg = (id & 0x1fff) * 4;
					val = RBIOS32(index);
					WREG32(reg, val);
					break;
				case 2:
					reg = (id & 0x1fff) * 4;
					and_mask = RBIOS32(index);
					index += 4;
					or_mask = RBIOS32(index);
					index += 4;
					val = RREG32(reg);
					val = (val & and_mask) | or_mask;
					WREG32(reg, val);
					break;
				case 4:
					val = RBIOS16(index);
					index += 2;
					udelay(val);
					break;
				case 5:
					reg = id & 0x1fff;
					and_mask = RBIOS32(index);
					index += 4;
					or_mask = RBIOS32(index);
					index += 4;
					val = RREG32_PLL(reg);
					val = (val & and_mask) | or_mask;
					WREG32_PLL(reg, val);
					break;
				case 6:
					reg = id & 0x1fff;
					val = RBIOS8(index);
					index += 1;
					radeon_i2c_put_byte(tmds->i2c_bus,
							    tmds->slave_addr,
							    reg, val);
					break;
				default:
					DRM_ERROR("Unknown id %d\n", id >> 13);
					break;
				}
				id = RBIOS16(index);
			}
			return true;
		}
	}
	return false;
}