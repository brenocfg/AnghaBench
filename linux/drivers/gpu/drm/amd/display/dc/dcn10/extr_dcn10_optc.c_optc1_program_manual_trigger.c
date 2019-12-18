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
 int /*<<< orphan*/  MANUAL_FLOW_CONTROL ; 
 int /*<<< orphan*/  OTG_MANUAL_FLOW_CONTROL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void optc1_program_manual_trigger(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_MANUAL_FLOW_CONTROL, 0,
			MANUAL_FLOW_CONTROL, 1);

	REG_SET(OTG_MANUAL_FLOW_CONTROL, 0,
			MANUAL_FLOW_CONTROL, 0);
}