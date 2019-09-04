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
struct TYPE_6__ {int /*<<< orphan*/  array_mode; int /*<<< orphan*/  pipe_config; int /*<<< orphan*/  tile_mode; int /*<<< orphan*/  tile_split; int /*<<< orphan*/  tile_aspect; int /*<<< orphan*/  bank_height; int /*<<< orphan*/  bank_width; int /*<<< orphan*/  num_banks; } ;
struct TYPE_4__ {int /*<<< orphan*/  shaderEnable; int /*<<< orphan*/  num_pipes; int /*<<< orphan*/  num_shader_engines; int /*<<< orphan*/  num_banks; int /*<<< orphan*/  swizzle; } ;
union dc_tiling_info {TYPE_3__ gfx8; TYPE_1__ gfx9; } ;
struct dce_mem_input {TYPE_2__* masks; } ;
struct TYPE_5__ {scalar_t__ GRPH_ARRAY_MODE; scalar_t__ GRPH_SW_MODE; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_ARRAY_MODE ; 
 int /*<<< orphan*/  GRPH_BANK_HEIGHT ; 
 int /*<<< orphan*/  GRPH_BANK_WIDTH ; 
 int /*<<< orphan*/  GRPH_COLOR_EXPANSION_MODE ; 
 int /*<<< orphan*/  GRPH_CONTROL ; 
 int /*<<< orphan*/  GRPH_MACRO_TILE_ASPECT ; 
 int /*<<< orphan*/  GRPH_MICRO_TILE_MODE ; 
 int /*<<< orphan*/  GRPH_NUM_BANKS ; 
 int /*<<< orphan*/  GRPH_NUM_PIPES ; 
 int /*<<< orphan*/  GRPH_NUM_SHADER_ENGINES ; 
 int /*<<< orphan*/  GRPH_PIPE_CONFIG ; 
 int /*<<< orphan*/  GRPH_SE_ENABLE ; 
 int /*<<< orphan*/  GRPH_SW_MODE ; 
 int /*<<< orphan*/  GRPH_TILE_SPLIT ; 
 int /*<<< orphan*/  REG_UPDATE_6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_tiling(
	struct dce_mem_input *dce_mi, const union dc_tiling_info *info)
{
	if (dce_mi->masks->GRPH_SW_MODE) { /* GFX9 */
		REG_UPDATE_6(GRPH_CONTROL,
				GRPH_SW_MODE, info->gfx9.swizzle,
				GRPH_NUM_BANKS, log_2(info->gfx9.num_banks),
				GRPH_NUM_SHADER_ENGINES, log_2(info->gfx9.num_shader_engines),
				GRPH_NUM_PIPES, log_2(info->gfx9.num_pipes),
				GRPH_COLOR_EXPANSION_MODE, 1,
				GRPH_SE_ENABLE, info->gfx9.shaderEnable);
		/* TODO: DCP0_GRPH_CONTROL__GRPH_SE_ENABLE where to get info
		GRPH_SE_ENABLE, 1,
		GRPH_Z, 0);
		 */
	}

	if (dce_mi->masks->GRPH_ARRAY_MODE) { /* GFX8 */
		REG_UPDATE_9(GRPH_CONTROL,
				GRPH_NUM_BANKS, info->gfx8.num_banks,
				GRPH_BANK_WIDTH, info->gfx8.bank_width,
				GRPH_BANK_HEIGHT, info->gfx8.bank_height,
				GRPH_MACRO_TILE_ASPECT, info->gfx8.tile_aspect,
				GRPH_TILE_SPLIT, info->gfx8.tile_split,
				GRPH_MICRO_TILE_MODE, info->gfx8.tile_mode,
				GRPH_PIPE_CONFIG, info->gfx8.pipe_config,
				GRPH_ARRAY_MODE, info->gfx8.array_mode,
				GRPH_COLOR_EXPANSION_MODE, 1);
		/* 01 - DCP_GRPH_COLOR_EXPANSION_MODE_ZEXP: zero expansion for YCbCr */
		/*
				GRPH_Z, 0);
				*/
	}
}