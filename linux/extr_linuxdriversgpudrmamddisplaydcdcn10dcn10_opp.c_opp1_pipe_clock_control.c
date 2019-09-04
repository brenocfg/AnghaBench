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
typedef  int uint32_t ;
struct output_pixel_processor {int dummy; } ;
struct dcn10_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPP_PIPE_CLOCK_EN ; 
 int /*<<< orphan*/  OPP_PIPE_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_opp* TO_DCN10_OPP (struct output_pixel_processor*) ; 

void opp1_pipe_clock_control(struct output_pixel_processor *opp, bool enable)
{
	struct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);
	uint32_t regval = enable ? 1 : 0;

	REG_UPDATE(OPP_PIPE_CONTROL, OPP_PIPE_CLOCK_EN, regval);
}