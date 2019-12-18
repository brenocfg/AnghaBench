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
struct timing_generator {int /*<<< orphan*/  inst; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  DWB_SOURCE_SELECT ; 
 int /*<<< orphan*/  OPTC_DWB0_SOURCE_SELECT ; 
 int /*<<< orphan*/  OPTC_DWB1_SOURCE_SELECT ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void optc2_set_dwb_source(struct timing_generator *optc,
		uint32_t dwb_pipe_inst)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	if (dwb_pipe_inst == 0)
		REG_UPDATE(DWB_SOURCE_SELECT,
				OPTC_DWB0_SOURCE_SELECT, optc->inst);
	else if (dwb_pipe_inst == 1)
		REG_UPDATE(DWB_SOURCE_SELECT,
				OPTC_DWB1_SOURCE_SELECT, optc->inst);
}