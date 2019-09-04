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
struct transform {int dummy; } ;
struct out_csc_color_matrix {int /*<<< orphan*/  color_space; } ;
struct dce_transform {int dummy; } ;
typedef  enum csc_color_mode { ____Placeholder_csc_color_mode } csc_color_mode ;

/* Variables and functions */
 int CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC ; 
 int /*<<< orphan*/  GRAPHICS_CSC_ADJUST_TYPE_SW ; 
 int /*<<< orphan*/  GRPH_COLOR_MATRIX_SW ; 
 struct dce_transform* TO_DCE_TRANSFORM (struct transform*) ; 
 int /*<<< orphan*/  configure_graphics_mode (struct dce_transform*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_color_matrix (struct dce_transform*,struct out_csc_color_matrix const*,int /*<<< orphan*/ ) ; 

void dce110_opp_set_csc_adjustment(
	struct transform *xfm,
	const struct out_csc_color_matrix *tbl_entry)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);
	enum csc_color_mode config =
			CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC;

	program_color_matrix(
			xfm_dce, tbl_entry, GRPH_COLOR_MATRIX_SW);

	/*  We did everything ,now program DxOUTPUT_CSC_CONTROL */
	configure_graphics_mode(xfm_dce, config, GRAPHICS_CSC_ADJUST_TYPE_SW,
			tbl_entry->color_space);
}