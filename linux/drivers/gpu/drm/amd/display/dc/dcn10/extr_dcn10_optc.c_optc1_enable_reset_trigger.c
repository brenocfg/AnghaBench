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
typedef  scalar_t__ uint32_t ;
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  OTG_FORCE_COUNT_NOW_MODE ; 
 int /*<<< orphan*/  OTG_TRIGA_CNTL ; 
 int /*<<< orphan*/  OTG_TRIGA_FALLING_EDGE_DETECT_CNTL ; 
 int /*<<< orphan*/  OTG_TRIGA_RISING_EDGE_DETECT_CNTL ; 
 int /*<<< orphan*/  OTG_TRIGA_SOURCE_PIPE_SELECT ; 
 int /*<<< orphan*/  OTG_TRIGA_SOURCE_SELECT ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_CNTL ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_POL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void optc1_enable_reset_trigger(struct timing_generator *optc, int source_tg_inst)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);
	uint32_t falling_edge;

	REG_GET(OTG_V_SYNC_A_CNTL,
			OTG_V_SYNC_A_POL, &falling_edge);

	if (falling_edge)
		REG_SET_3(OTG_TRIGA_CNTL, 0,
				/* vsync signal from selected OTG pipe based
				 * on OTG_TRIG_SOURCE_PIPE_SELECT setting
				 */
				OTG_TRIGA_SOURCE_SELECT, 20,
				OTG_TRIGA_SOURCE_PIPE_SELECT, source_tg_inst,
				/* always detect falling edge */
				OTG_TRIGA_FALLING_EDGE_DETECT_CNTL, 1);
	else
		REG_SET_3(OTG_TRIGA_CNTL, 0,
				/* vsync signal from selected OTG pipe based
				 * on OTG_TRIG_SOURCE_PIPE_SELECT setting
				 */
				OTG_TRIGA_SOURCE_SELECT, 20,
				OTG_TRIGA_SOURCE_PIPE_SELECT, source_tg_inst,
				/* always detect rising edge */
				OTG_TRIGA_RISING_EDGE_DETECT_CNTL, 1);

	REG_SET(OTG_FORCE_COUNT_NOW_CNTL, 0,
			/* force H count to H_TOTAL and V count to V_TOTAL in
			 * progressive mode and V_TOTAL-1 in interlaced mode
			 */
			OTG_FORCE_COUNT_NOW_MODE, 2);
}