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
typedef  int /*<<< orphan*/  uint32_t ;
struct output_pixel_processor {int dummy; } ;
struct dce110_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  FMT420_MEM0_PWR_FORCE ; 
 int /*<<< orphan*/  FMT420_MEM0_SOURCE_SEL ; 
 int /*<<< orphan*/  FMT_CONTROL ; 
 int /*<<< orphan*/  FMT_SRC_SELECT ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dce110_opp* TO_DCE110_OPP (struct output_pixel_processor*) ; 

__attribute__((used)) static void program_formatter_420_memory(struct output_pixel_processor *opp)
{
	struct dce110_opp *opp110 = TO_DCE110_OPP(opp);
	uint32_t fmt_mem_cntl_value;

	/* Program source select*/
	/* Use HW default source select for FMT_MEMORYx_CONTROL */
	/* Use that value for FMT_SRC_SELECT as well*/
	REG_GET(CONTROL,
			FMT420_MEM0_SOURCE_SEL, &fmt_mem_cntl_value);

	REG_UPDATE(FMT_CONTROL,
			FMT_SRC_SELECT, fmt_mem_cntl_value);

	/* Turn on the memory */
	REG_UPDATE(CONTROL,
			FMT420_MEM0_PWR_FORCE, 0);
}