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
struct TYPE_2__ {int /*<<< orphan*/  pipe_aligned; int /*<<< orphan*/  rb_aligned; int /*<<< orphan*/  meta_linear; int /*<<< orphan*/  swizzle; int /*<<< orphan*/  max_compressed_frags; int /*<<< orphan*/  num_rb_per_se; int /*<<< orphan*/  num_shader_engines; int /*<<< orphan*/  pipe_interleave; int /*<<< orphan*/  num_banks; int /*<<< orphan*/  num_pipes; } ;
union dc_tiling_info {TYPE_1__ gfx9; } ;
struct hubp {int dummy; } ;
struct dcn10_hubp {int dummy; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  DCSURF_ADDR_CONFIG ; 
 int /*<<< orphan*/  DCSURF_TILING_CONFIG ; 
 int /*<<< orphan*/  MAX_COMPRESSED_FRAGS ; 
 int /*<<< orphan*/  META_LINEAR ; 
 int /*<<< orphan*/  NUM_BANKS ; 
 int /*<<< orphan*/  NUM_PIPES ; 
 int /*<<< orphan*/  NUM_RB_PER_SE ; 
 int /*<<< orphan*/  NUM_SE ; 
 int /*<<< orphan*/  PIPE_ALIGNED ; 
 int /*<<< orphan*/  PIPE_INTERLEAVE ; 
 int /*<<< orphan*/  RB_ALIGNED ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_MODE ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 
 int /*<<< orphan*/  log_2 (int /*<<< orphan*/ ) ; 

void hubp1_program_tiling(
	struct hubp *hubp,
	const union dc_tiling_info *info,
	const enum surface_pixel_format pixel_format)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE_6(DCSURF_ADDR_CONFIG,
			NUM_PIPES, log_2(info->gfx9.num_pipes),
			NUM_BANKS, log_2(info->gfx9.num_banks),
			PIPE_INTERLEAVE, info->gfx9.pipe_interleave,
			NUM_SE, log_2(info->gfx9.num_shader_engines),
			NUM_RB_PER_SE, log_2(info->gfx9.num_rb_per_se),
			MAX_COMPRESSED_FRAGS, log_2(info->gfx9.max_compressed_frags));

	REG_UPDATE_4(DCSURF_TILING_CONFIG,
			SW_MODE, info->gfx9.swizzle,
			META_LINEAR, info->gfx9.meta_linear,
			RB_ALIGNED, info->gfx9.rb_aligned,
			PIPE_ALIGNED, info->gfx9.pipe_aligned);
}