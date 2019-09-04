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
typedef  int /*<<< orphan*/  uint32_t ;
struct transform {int /*<<< orphan*/  ctx; } ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 130 
#define  COLOR_DEPTH_121212 129 
#define  COLOR_DEPTH_888 128 
 int /*<<< orphan*/  DENORM_10BIT_OUT ; 
 int /*<<< orphan*/  DENORM_CLAMP_CONTROL ; 
 int /*<<< orphan*/  DENORM_MODE ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDENORM_CLAMP_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_Denormalization(struct transform *xfm,
		enum dc_color_depth color_depth)
{
	uint32_t value = dm_read_reg(xfm->ctx, mmDENORM_CLAMP_CONTROL);

	switch (color_depth) {
	case COLOR_DEPTH_888:
		/* 255/256 for 8 bit output color depth */
		set_reg_field_value(
			value,
			1,
			DENORM_CLAMP_CONTROL,
			DENORM_MODE);
		break;
	case COLOR_DEPTH_101010:
		/* 1023/1024 for 10 bit output color depth */
		set_reg_field_value(
			value,
			2,
			DENORM_CLAMP_CONTROL,
			DENORM_MODE);
		break;
	case COLOR_DEPTH_121212:
		/* 4095/4096 for 12 bit output color depth */
		set_reg_field_value(
			value,
			3,
			DENORM_CLAMP_CONTROL,
			DENORM_MODE);
		break;
	default:
		/* not valid case */
		break;
	}

	set_reg_field_value(
		value,
		1,
		DENORM_CLAMP_CONTROL,
		DENORM_10BIT_OUT);

	dm_write_reg(xfm->ctx, mmDENORM_CLAMP_CONTROL, value);
}