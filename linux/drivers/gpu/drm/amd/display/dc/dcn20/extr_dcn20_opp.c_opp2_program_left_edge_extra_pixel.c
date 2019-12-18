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
struct output_pixel_processor {int dummy; } ;
struct dcn20_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_422_CONTROL ; 
 int /*<<< orphan*/  FMT_LEFT_EDGE_EXTRA_PIXEL_COUNT ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_opp* TO_DCN20_OPP (struct output_pixel_processor*) ; 

void opp2_program_left_edge_extra_pixel (
		struct output_pixel_processor *opp,
		bool count)
{
	struct dcn20_opp *oppn20 = TO_DCN20_OPP(opp);

	/* Specifies the number of extra left edge pixels that are supplied to
	 * the 422 horizontal chroma sub-sample filter.
	 * Note that when left edge pixel is not "0", fmt pixel encoding can be in either 420 or 422 mode
	 * */
	REG_UPDATE(FMT_422_CONTROL, FMT_LEFT_EDGE_EXTRA_PIXEL_COUNT, count);
}