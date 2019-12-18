#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_2__ {scalar_t__ usb_err; } ;
struct sd {size_t* sensor_reg_cache; int bridge; TYPE_1__ gspca_dev; } ;

/* Variables and functions */
#define  BRIDGE_OV511 134 
#define  BRIDGE_OV511PLUS 133 
#define  BRIDGE_OV518 132 
#define  BRIDGE_OV518PLUS 131 
#define  BRIDGE_OV519 130 
#define  BRIDGE_OVFX2 129 
#define  BRIDGE_W9968CF 128 
 int /*<<< orphan*/  memset (size_t*,int,int) ; 
 int /*<<< orphan*/  ov511_i2c_w (struct sd*,size_t,size_t) ; 
 int /*<<< orphan*/  ov518_i2c_w (struct sd*,size_t,size_t) ; 
 int /*<<< orphan*/  ovfx2_i2c_w (struct sd*,size_t,size_t) ; 
 int /*<<< orphan*/  w9968cf_i2c_w (struct sd*,size_t,size_t) ; 

__attribute__((used)) static void i2c_w(struct sd *sd, u8 reg, u8 value)
{
	if (sd->sensor_reg_cache[reg] == value)
		return;

	switch (sd->bridge) {
	case BRIDGE_OV511:
	case BRIDGE_OV511PLUS:
		ov511_i2c_w(sd, reg, value);
		break;
	case BRIDGE_OV518:
	case BRIDGE_OV518PLUS:
	case BRIDGE_OV519:
		ov518_i2c_w(sd, reg, value);
		break;
	case BRIDGE_OVFX2:
		ovfx2_i2c_w(sd, reg, value);
		break;
	case BRIDGE_W9968CF:
		w9968cf_i2c_w(sd, reg, value);
		break;
	}

	if (sd->gspca_dev.usb_err >= 0) {
		/* Up on sensor reset empty the register cache */
		if (reg == 0x12 && (value & 0x80))
			memset(sd->sensor_reg_cache, -1,
				sizeof(sd->sensor_reg_cache));
		else
			sd->sensor_reg_cache[reg] = value;
	}
}