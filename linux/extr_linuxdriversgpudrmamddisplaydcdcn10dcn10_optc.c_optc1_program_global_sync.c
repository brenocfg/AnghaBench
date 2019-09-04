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
struct TYPE_2__ {scalar_t__ vstartup_start; scalar_t__ vready_offset; int /*<<< orphan*/  vupdate_width; int /*<<< orphan*/  vupdate_offset; } ;
struct timing_generator {TYPE_1__ dlg_otg_param; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_VREADY_PARAM ; 
 int /*<<< orphan*/  OTG_VSTARTUP_PARAM ; 
 int /*<<< orphan*/  OTG_VUPDATE_PARAM ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VREADY_OFFSET ; 
 int /*<<< orphan*/  VSTARTUP_START ; 
 int /*<<< orphan*/  VUPDATE_OFFSET ; 
 int /*<<< orphan*/  VUPDATE_WIDTH ; 

void optc1_program_global_sync(
		struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	if (optc->dlg_otg_param.vstartup_start == 0) {
		BREAK_TO_DEBUGGER();
		return;
	}

	REG_SET(OTG_VSTARTUP_PARAM, 0,
		VSTARTUP_START, optc->dlg_otg_param.vstartup_start);

	REG_SET_2(OTG_VUPDATE_PARAM, 0,
			VUPDATE_OFFSET, optc->dlg_otg_param.vupdate_offset,
			VUPDATE_WIDTH, optc->dlg_otg_param.vupdate_width);

	REG_SET(OTG_VREADY_PARAM, 0,
			VREADY_OFFSET, optc->dlg_otg_param.vready_offset);
}