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
typedef  scalar_t__ uint32_t ;
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct dce110_timing_generator {int controller_id; } ;

/* Variables and functions */
#define  CONTROLLER_ID_D0 133 
#define  CONTROLLER_ID_D1 132 
#define  CONTROLLER_ID_D2 131 
#define  CONTROLLER_ID_D3 130 
#define  CONTROLLER_ID_D4 129 
#define  CONTROLLER_ID_D5 128 
 int /*<<< orphan*/  D1VGA_CONTROL ; 
 int /*<<< orphan*/  D1VGA_MODE_ENABLE ; 
 int /*<<< orphan*/  D1VGA_OVERSCAN_COLOR_EN ; 
 int /*<<< orphan*/  D1VGA_SYNC_POLARITY_SELECT ; 
 int /*<<< orphan*/  D1VGA_TIMING_SELECT ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 scalar_t__ dm_read_reg_soc15 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dm_write_reg_soc15 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mmD1VGA_CONTROL ; 
 scalar_t__ mmD2VGA_CONTROL ; 
 scalar_t__ mmD3VGA_CONTROL ; 
 scalar_t__ mmD4VGA_CONTROL ; 
 scalar_t__ mmD5VGA_CONTROL ; 
 scalar_t__ mmD6VGA_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce120_timing_generator_disable_vga(struct timing_generator *tg)
{
	uint32_t offset = 0;
	uint32_t value = 0;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	switch (tg110->controller_id) {
	case CONTROLLER_ID_D0:
		offset = 0;
		break;
	case CONTROLLER_ID_D1:
		offset = mmD2VGA_CONTROL - mmD1VGA_CONTROL;
		break;
	case CONTROLLER_ID_D2:
		offset = mmD3VGA_CONTROL - mmD1VGA_CONTROL;
		break;
	case CONTROLLER_ID_D3:
		offset = mmD4VGA_CONTROL - mmD1VGA_CONTROL;
		break;
	case CONTROLLER_ID_D4:
		offset = mmD5VGA_CONTROL - mmD1VGA_CONTROL;
		break;
	case CONTROLLER_ID_D5:
		offset = mmD6VGA_CONTROL - mmD1VGA_CONTROL;
		break;
	default:
		break;
	}

	value = dm_read_reg_soc15(tg->ctx, mmD1VGA_CONTROL, offset);

	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_MODE_ENABLE);
	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_TIMING_SELECT);
	set_reg_field_value(
			value, 0, D1VGA_CONTROL, D1VGA_SYNC_POLARITY_SELECT);
	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_OVERSCAN_COLOR_EN);

	dm_write_reg_soc15(tg->ctx, mmD1VGA_CONTROL, offset, value);
}