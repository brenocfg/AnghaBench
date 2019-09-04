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
struct radeon_encoder_ext_tmds {int dvo_chip; int /*<<< orphan*/  slave_addr; int /*<<< orphan*/  i2c_bus; } ;
struct radeon_encoder {struct radeon_encoder_ext_tmds* enc_priv; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
#define  DVO_SIL1178 129 
#define  DVO_SIL164 128 
 int /*<<< orphan*/  radeon_i2c_put_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void radeon_external_tmds_setup(struct drm_encoder *encoder)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_ext_tmds *tmds = radeon_encoder->enc_priv;

	if (!tmds)
		return;

	switch (tmds->dvo_chip) {
	case DVO_SIL164:
		/* sil 164 */
		radeon_i2c_put_byte(tmds->i2c_bus,
				    tmds->slave_addr,
				    0x08, 0x30);
		radeon_i2c_put_byte(tmds->i2c_bus,
				       tmds->slave_addr,
				       0x09, 0x00);
		radeon_i2c_put_byte(tmds->i2c_bus,
				    tmds->slave_addr,
				    0x0a, 0x90);
		radeon_i2c_put_byte(tmds->i2c_bus,
				    tmds->slave_addr,
				    0x0c, 0x89);
		radeon_i2c_put_byte(tmds->i2c_bus,
				       tmds->slave_addr,
				       0x08, 0x3b);
		break;
	case DVO_SIL1178:
		/* sil 1178 - untested */
		/*
		 * 0x0f, 0x44
		 * 0x0f, 0x4c
		 * 0x0e, 0x01
		 * 0x0a, 0x80
		 * 0x09, 0x30
		 * 0x0c, 0xc9
		 * 0x0d, 0x70
		 * 0x08, 0x32
		 * 0x08, 0x33
		 */
		break;
	default:
		break;
	}

}