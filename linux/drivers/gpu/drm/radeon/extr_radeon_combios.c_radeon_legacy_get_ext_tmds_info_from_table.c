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
struct radeon_i2c_bus_rec {int dummy; } ;
struct radeon_encoder_ext_tmds {int slave_addr; int /*<<< orphan*/  dvo_chip; int /*<<< orphan*/  i2c_bus; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct TYPE_4__ {int connector_table; } ;
struct radeon_device {TYPE_2__ mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
#define  CT_MINI_EXTERNAL 129 
#define  CT_POWERBOOK_EXTERNAL 128 
 int /*<<< orphan*/  DDC_MONID ; 
 int /*<<< orphan*/  DVO_SIL164 ; 
 struct radeon_i2c_bus_rec combios_setup_i2c_bus (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_i2c_lookup (struct radeon_device*,struct radeon_i2c_bus_rec*) ; 

bool radeon_legacy_get_ext_tmds_info_from_table(struct radeon_encoder *encoder,
						struct radeon_encoder_ext_tmds *tmds)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_i2c_bus_rec i2c_bus;

	/* default for macs */
	i2c_bus = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
	tmds->i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);

	/* XXX some macs have duallink chips */
	switch (rdev->mode_info.connector_table) {
	case CT_POWERBOOK_EXTERNAL:
	case CT_MINI_EXTERNAL:
	default:
		tmds->dvo_chip = DVO_SIL164;
		tmds->slave_addr = 0x70 >> 1; /* 7 bit addressing */
		break;
	}

	return true;
}