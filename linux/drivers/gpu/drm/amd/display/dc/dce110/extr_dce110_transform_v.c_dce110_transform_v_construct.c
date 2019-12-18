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
struct TYPE_2__ {int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dce_transform {int lb_pixel_depth_supported; int prescaler_on; int /*<<< orphan*/  lb_memory_size; int /*<<< orphan*/  lb_bits_per_entry; TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LB_BITS_PER_ENTRY ; 
 int LB_PIXEL_DEPTH_18BPP ; 
 int LB_PIXEL_DEPTH_24BPP ; 
 int LB_PIXEL_DEPTH_30BPP ; 
 int /*<<< orphan*/  LB_TOTAL_NUMBER_OF_ENTRIES ; 
 int /*<<< orphan*/  dce110_xfmv_funcs ; 

bool dce110_transform_v_construct(
	struct dce_transform *xfm_dce,
	struct dc_context *ctx)
{
	xfm_dce->base.ctx = ctx;

	xfm_dce->base.funcs = &dce110_xfmv_funcs;

	xfm_dce->lb_pixel_depth_supported =
			LB_PIXEL_DEPTH_18BPP |
			LB_PIXEL_DEPTH_24BPP |
			LB_PIXEL_DEPTH_30BPP;

	xfm_dce->prescaler_on = true;
	xfm_dce->lb_bits_per_entry = LB_BITS_PER_ENTRY;
	xfm_dce->lb_memory_size = LB_TOTAL_NUMBER_OF_ENTRIES; /*0x6B0*/

	return true;
}