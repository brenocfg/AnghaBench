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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  GSL0_READY_SOURCE_SEL ; 
 int /*<<< orphan*/  GSL1_READY_SOURCE_SEL ; 
 int /*<<< orphan*/  GSL2_READY_SOURCE_SEL ; 
 int /*<<< orphan*/  GSL_SOURCE_SELECT ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void optc2_set_gsl_source_select(
		struct timing_generator *optc,
		int group_idx,
		uint32_t gsl_ready_signal)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	switch (group_idx) {
	case 1:
		REG_UPDATE(GSL_SOURCE_SELECT, GSL0_READY_SOURCE_SEL, gsl_ready_signal);
		break;
	case 2:
		REG_UPDATE(GSL_SOURCE_SELECT, GSL1_READY_SOURCE_SEL, gsl_ready_signal);
		break;
	case 3:
		REG_UPDATE(GSL_SOURCE_SELECT, GSL2_READY_SOURCE_SEL, gsl_ready_signal);
		break;
	default:
		break;
	}
}