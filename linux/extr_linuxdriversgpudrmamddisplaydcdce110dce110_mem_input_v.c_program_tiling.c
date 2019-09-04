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
struct TYPE_3__ {int num_banks; int bank_width; int bank_height; int tile_aspect; int tile_split; int tile_mode; int pipe_config; int array_mode; int bank_width_c; int bank_height_c; int tile_aspect_c; int tile_split_c; int tile_mode_c; } ;
union dc_tiling_info {TYPE_1__ gfx8; } ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
struct dce_mem_input {TYPE_2__ base; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_ARRAY_MODE ; 
 int /*<<< orphan*/  GRPH_BANK_HEIGHT_C ; 
 int /*<<< orphan*/  GRPH_BANK_HEIGHT_L ; 
 int /*<<< orphan*/  GRPH_BANK_WIDTH_C ; 
 int /*<<< orphan*/  GRPH_BANK_WIDTH_L ; 
 int /*<<< orphan*/  GRPH_COLOR_EXPANSION_MODE ; 
 int /*<<< orphan*/  GRPH_MACRO_TILE_ASPECT_C ; 
 int /*<<< orphan*/  GRPH_MACRO_TILE_ASPECT_L ; 
 int /*<<< orphan*/  GRPH_MICRO_TILE_MODE_C ; 
 int /*<<< orphan*/  GRPH_MICRO_TILE_MODE_L ; 
 int /*<<< orphan*/  GRPH_NUM_BANKS ; 
 int /*<<< orphan*/  GRPH_PIPE_CONFIG ; 
 int /*<<< orphan*/  GRPH_TILE_SPLIT_C ; 
 int /*<<< orphan*/  GRPH_TILE_SPLIT_L ; 
 int /*<<< orphan*/  GRPH_Z ; 
 int /*<<< orphan*/  UNP_GRPH_CONTROL ; 
 int /*<<< orphan*/  UNP_GRPH_CONTROL_C ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmUNP_GRPH_CONTROL ; 
 int /*<<< orphan*/  mmUNP_GRPH_CONTROL_C ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_tiling(
	struct dce_mem_input *mem_input110,
	const union dc_tiling_info *info,
	const enum surface_pixel_format pixel_format)
{
	uint32_t value = 0;

	set_reg_field_value(value, info->gfx8.num_banks,
		UNP_GRPH_CONTROL, GRPH_NUM_BANKS);

	set_reg_field_value(value, info->gfx8.bank_width,
		UNP_GRPH_CONTROL, GRPH_BANK_WIDTH_L);

	set_reg_field_value(value, info->gfx8.bank_height,
		UNP_GRPH_CONTROL, GRPH_BANK_HEIGHT_L);

	set_reg_field_value(value, info->gfx8.tile_aspect,
		UNP_GRPH_CONTROL, GRPH_MACRO_TILE_ASPECT_L);

	set_reg_field_value(value, info->gfx8.tile_split,
		UNP_GRPH_CONTROL, GRPH_TILE_SPLIT_L);

	set_reg_field_value(value, info->gfx8.tile_mode,
		UNP_GRPH_CONTROL, GRPH_MICRO_TILE_MODE_L);

	set_reg_field_value(value, info->gfx8.pipe_config,
		UNP_GRPH_CONTROL, GRPH_PIPE_CONFIG);

	set_reg_field_value(value, info->gfx8.array_mode,
		UNP_GRPH_CONTROL, GRPH_ARRAY_MODE);

	set_reg_field_value(value, 1,
		UNP_GRPH_CONTROL, GRPH_COLOR_EXPANSION_MODE);

	set_reg_field_value(value, 0,
		UNP_GRPH_CONTROL, GRPH_Z);

	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_CONTROL,
		value);

	value = 0;

	set_reg_field_value(value, info->gfx8.bank_width_c,
		UNP_GRPH_CONTROL_C, GRPH_BANK_WIDTH_C);

	set_reg_field_value(value, info->gfx8.bank_height_c,
		UNP_GRPH_CONTROL_C, GRPH_BANK_HEIGHT_C);

	set_reg_field_value(value, info->gfx8.tile_aspect_c,
		UNP_GRPH_CONTROL_C, GRPH_MACRO_TILE_ASPECT_C);

	set_reg_field_value(value, info->gfx8.tile_split_c,
		UNP_GRPH_CONTROL_C, GRPH_TILE_SPLIT_C);

	set_reg_field_value(value, info->gfx8.tile_mode_c,
		UNP_GRPH_CONTROL_C, GRPH_MICRO_TILE_MODE_C);

	dm_write_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_CONTROL_C,
		value);
}