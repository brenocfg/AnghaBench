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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OPTC_INPUT_GLOBAL_CONTROL ; 
 int /*<<< orphan*/  OPTC_UNDERFLOW_CLEAR ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void optc1_clear_optc_underflow(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE(OPTC_INPUT_GLOBAL_CONTROL, OPTC_UNDERFLOW_CLEAR, 1);
}