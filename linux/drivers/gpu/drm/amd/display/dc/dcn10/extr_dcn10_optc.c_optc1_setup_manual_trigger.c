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
struct timing_generator {int /*<<< orphan*/  inst; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  MANUAL_FLOW_CONTROL_SEL ; 
 int /*<<< orphan*/  OTG_GLOBAL_CONTROL2 ; 
 int /*<<< orphan*/  OTG_TRIGA_CLEAR ; 
 int /*<<< orphan*/  OTG_TRIGA_CNTL ; 
 int /*<<< orphan*/  OTG_TRIGA_DELAY ; 
 int /*<<< orphan*/  OTG_TRIGA_FALLING_EDGE_DETECT_CNTL ; 
 int /*<<< orphan*/  OTG_TRIGA_FREQUENCY_SELECT ; 
 int /*<<< orphan*/  OTG_TRIGA_POLARITY_SELECT ; 
 int /*<<< orphan*/  OTG_TRIGA_RISING_EDGE_DETECT_CNTL ; 
 int /*<<< orphan*/  OTG_TRIGA_SOURCE_PIPE_SELECT ; 
 int /*<<< orphan*/  OTG_TRIGA_SOURCE_SELECT ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void optc1_setup_manual_trigger(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_GLOBAL_CONTROL2, 0,
			MANUAL_FLOW_CONTROL_SEL, optc->inst);

	REG_SET_8(OTG_TRIGA_CNTL, 0,
			OTG_TRIGA_SOURCE_SELECT, 22,
			OTG_TRIGA_SOURCE_PIPE_SELECT, optc->inst,
			OTG_TRIGA_RISING_EDGE_DETECT_CNTL, 1,
			OTG_TRIGA_FALLING_EDGE_DETECT_CNTL, 0,
			OTG_TRIGA_POLARITY_SELECT, 0,
			OTG_TRIGA_FREQUENCY_SELECT, 0,
			OTG_TRIGA_DELAY, 0,
			OTG_TRIGA_CLEAR, 1);
}