#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int x; int y; int width; int height; } ;
struct TYPE_4__ {int x; int y; int width; int height; } ;
struct plane_size {int surface_pitch; int chroma_pitch; TYPE_2__ chroma_size; TYPE_1__ surface_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; } ;
struct dce_mem_input {TYPE_3__ base; } ;
typedef  enum dc_rotation_angle { ____Placeholder_dc_rotation_angle } dc_rotation_angle ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_PITCH_C ; 
 int /*<<< orphan*/  GRPH_PITCH_L ; 
 int /*<<< orphan*/  GRPH_X_END_C ; 
 int /*<<< orphan*/  GRPH_X_END_L ; 
 int /*<<< orphan*/  GRPH_X_START_C ; 
 int /*<<< orphan*/  GRPH_X_START_L ; 
 int /*<<< orphan*/  GRPH_Y_END_C ; 
 int /*<<< orphan*/  GRPH_Y_END_L ; 
 int /*<<< orphan*/  GRPH_Y_START_C ; 
 int /*<<< orphan*/  GRPH_Y_START_L ; 
 int /*<<< orphan*/  ROTATION_ANGLE ; 
#define  ROTATION_ANGLE_180 130 
#define  ROTATION_ANGLE_270 129 
#define  ROTATION_ANGLE_90 128 
 int /*<<< orphan*/  UNP_GRPH_PITCH_C ; 
 int /*<<< orphan*/  UNP_GRPH_PITCH_L ; 
 int /*<<< orphan*/  UNP_GRPH_X_END_C ; 
 int /*<<< orphan*/  UNP_GRPH_X_END_L ; 
 int /*<<< orphan*/  UNP_GRPH_X_START_C ; 
 int /*<<< orphan*/  UNP_GRPH_X_START_L ; 
 int /*<<< orphan*/  UNP_GRPH_Y_END_C ; 
 int /*<<< orphan*/  UNP_GRPH_Y_END_L ; 
 int /*<<< orphan*/  UNP_GRPH_Y_START_C ; 
 int /*<<< orphan*/  UNP_GRPH_Y_START_L ; 
 int /*<<< orphan*/  UNP_HW_ROTATION ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmUNP_GRPH_PITCH_C ; 
 int /*<<< orphan*/  mmUNP_GRPH_PITCH_L ; 
 int /*<<< orphan*/  mmUNP_GRPH_X_END_C ; 
 int /*<<< orphan*/  mmUNP_GRPH_X_END_L ; 
 int /*<<< orphan*/  mmUNP_GRPH_X_START_C ; 
 int /*<<< orphan*/  mmUNP_GRPH_X_START_L ; 
 int /*<<< orphan*/  mmUNP_GRPH_Y_END_C ; 
 int /*<<< orphan*/  mmUNP_GRPH_Y_END_L ; 
 int /*<<< orphan*/  mmUNP_GRPH_Y_START_C ; 
 int /*<<< orphan*/  mmUNP_GRPH_Y_START_L ; 
 int /*<<< orphan*/  mmUNP_HW_ROTATION ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static void program_size_and_rotation(
	struct dce_mem_input *mem_input110,
	enum dc_rotation_angle rotation,
	const struct plane_size *plane_size)
{
	uint32_t value = 0;
	struct plane_size local_size = *plane_size;

	if (rotation == ROTATION_ANGLE_90 ||
		rotation == ROTATION_ANGLE_270) {

		swap(local_size.surface_size.x,
		     local_size.surface_size.y);
		swap(local_size.surface_size.width,
		     local_size.surface_size.height);
		swap(local_size.chroma_size.x,
		     local_size.chroma_size.y);
		swap(local_size.chroma_size.width,
		     local_size.chroma_size.height);
	}

	value = 0;
	set_reg_field_value(value, local_size.surface_pitch,
			UNP_GRPH_PITCH_L, GRPH_PITCH_L);

	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PITCH_L,
		value);

	value = 0;
	set_reg_field_value(value, local_size.chroma_pitch,
			UNP_GRPH_PITCH_C, GRPH_PITCH_C);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PITCH_C,
		value);

	value = 0;
	set_reg_field_value(value, 0,
			UNP_GRPH_X_START_L, GRPH_X_START_L);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_X_START_L,
		value);

	value = 0;
	set_reg_field_value(value, 0,
			UNP_GRPH_X_START_C, GRPH_X_START_C);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_X_START_C,
		value);

	value = 0;
	set_reg_field_value(value, 0,
			UNP_GRPH_Y_START_L, GRPH_Y_START_L);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_Y_START_L,
		value);

	value = 0;
	set_reg_field_value(value, 0,
			UNP_GRPH_Y_START_C, GRPH_Y_START_C);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_Y_START_C,
		value);

	value = 0;
	set_reg_field_value(value, local_size.surface_size.x +
			local_size.surface_size.width,
			UNP_GRPH_X_END_L, GRPH_X_END_L);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_X_END_L,
		value);

	value = 0;
	set_reg_field_value(value, local_size.chroma_size.x +
			local_size.chroma_size.width,
			UNP_GRPH_X_END_C, GRPH_X_END_C);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_X_END_C,
		value);

	value = 0;
	set_reg_field_value(value, local_size.surface_size.y +
			local_size.surface_size.height,
			UNP_GRPH_Y_END_L, GRPH_Y_END_L);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_Y_END_L,
		value);

	value = 0;
	set_reg_field_value(value, local_size.chroma_size.y +
			local_size.chroma_size.height,
			UNP_GRPH_Y_END_C, GRPH_Y_END_C);
	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_Y_END_C,
		value);

	value = 0;
	switch (rotation) {
	case ROTATION_ANGLE_90:
		set_reg_field_value(value, 3,
			UNP_HW_ROTATION, ROTATION_ANGLE);
		break;
	case ROTATION_ANGLE_180:
		set_reg_field_value(value, 2,
			UNP_HW_ROTATION, ROTATION_ANGLE);
		break;
	case ROTATION_ANGLE_270:
		set_reg_field_value(value, 1,
			UNP_HW_ROTATION, ROTATION_ANGLE);
		break;
	default:
		set_reg_field_value(value, 0,
			UNP_HW_ROTATION, ROTATION_ANGLE);
		break;
	}

	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_HW_ROTATION,
		value);
}