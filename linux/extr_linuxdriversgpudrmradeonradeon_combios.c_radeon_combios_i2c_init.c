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
struct radeon_i2c_bus_rec {int valid; int hw_capable; int mm_i2c; int i2c_id; } ;
struct radeon_device {scalar_t__ family; void** i2c_bus; struct drm_device* ddev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_R200 ; 
 scalar_t__ CHIP_R300 ; 
 scalar_t__ CHIP_R350 ; 
 scalar_t__ CHIP_RS300 ; 
 scalar_t__ CHIP_RS400 ; 
 scalar_t__ CHIP_RS480 ; 
 int /*<<< orphan*/  DDC_CRT2 ; 
 int /*<<< orphan*/  DDC_DVI ; 
 int /*<<< orphan*/  DDC_MONID ; 
 int /*<<< orphan*/  DDC_VGA ; 
 struct radeon_i2c_bus_rec combios_setup_i2c_bus (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_i2c_bus_rec radeon_combios_get_i2c_info_from_table (struct radeon_device*) ; 
 void* radeon_i2c_create (struct drm_device*,struct radeon_i2c_bus_rec*,char*) ; 

void radeon_combios_i2c_init(struct radeon_device *rdev)
{
	struct drm_device *dev = rdev->ddev;
	struct radeon_i2c_bus_rec i2c;

	/* actual hw pads
	 * r1xx/rs2xx/rs3xx
	 * 0x60, 0x64, 0x68, 0x6c, gpiopads, mm
	 * r200
	 * 0x60, 0x64, 0x68, mm
	 * r300/r350
	 * 0x60, 0x64, mm
	 * rv2xx/rv3xx/rs4xx
	 * 0x60, 0x64, 0x68, gpiopads, mm
	 */

	/* 0x60 */
	i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
	rdev->i2c_bus[0] = radeon_i2c_create(dev, &i2c, "DVI_DDC");
	/* 0x64 */
	i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
	rdev->i2c_bus[1] = radeon_i2c_create(dev, &i2c, "VGA_DDC");

	/* mm i2c */
	i2c.valid = true;
	i2c.hw_capable = true;
	i2c.mm_i2c = true;
	i2c.i2c_id = 0xa0;
	rdev->i2c_bus[2] = radeon_i2c_create(dev, &i2c, "MM_I2C");

	if (rdev->family == CHIP_R300 ||
	    rdev->family == CHIP_R350) {
		/* only 2 sw i2c pads */
	} else if (rdev->family == CHIP_RS300 ||
		   rdev->family == CHIP_RS400 ||
		   rdev->family == CHIP_RS480) {
		/* 0x68 */
		i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		rdev->i2c_bus[3] = radeon_i2c_create(dev, &i2c, "MONID");

		/* gpiopad */
		i2c = radeon_combios_get_i2c_info_from_table(rdev);
		if (i2c.valid)
			rdev->i2c_bus[4] = radeon_i2c_create(dev, &i2c, "GPIOPAD_MASK");
	} else if ((rdev->family == CHIP_R200) ||
		   (rdev->family >= CHIP_R300)) {
		/* 0x68 */
		i2c = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		rdev->i2c_bus[3] = radeon_i2c_create(dev, &i2c, "MONID");
	} else {
		/* 0x68 */
		i2c = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		rdev->i2c_bus[3] = radeon_i2c_create(dev, &i2c, "MONID");
		/* 0x6c */
		i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		rdev->i2c_bus[4] = radeon_i2c_create(dev, &i2c, "CRT2_DDC");
	}
}