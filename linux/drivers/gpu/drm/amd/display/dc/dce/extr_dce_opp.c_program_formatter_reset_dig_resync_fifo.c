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
struct dce110_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_420_PIXEL_PHASE_LOCKED ; 
 int /*<<< orphan*/  FMT_420_PIXEL_PHASE_LOCKED_CLEAR ; 
 int /*<<< orphan*/  FMT_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct dce110_opp* TO_DCE110_OPP (struct output_pixel_processor*) ; 

__attribute__((used)) static void program_formatter_reset_dig_resync_fifo(struct output_pixel_processor *opp)
{
	struct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	/* clear previous phase lock status*/
	REG_UPDATE(FMT_CONTROL,
			FMT_420_PIXEL_PHASE_LOCKED_CLEAR, 1);

	/* poll until FMT_420_PIXEL_PHASE_LOCKED become 1*/
	REG_WAIT(FMT_CONTROL, FMT_420_PIXEL_PHASE_LOCKED, 1, 10, 10);

}