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
struct optc {int dummy; } ;
struct dcn_otg_state {int /*<<< orphan*/  underflow_occurred_status; int /*<<< orphan*/  h_total; int /*<<< orphan*/  h_sync_a_pol; int /*<<< orphan*/  h_sync_a_end; int /*<<< orphan*/  h_sync_a_start; int /*<<< orphan*/  h_blank_end; int /*<<< orphan*/  h_blank_start; int /*<<< orphan*/  v_sync_a_end; int /*<<< orphan*/  v_sync_a_start; int /*<<< orphan*/  v_total_min_sel; int /*<<< orphan*/  v_total_max_sel; int /*<<< orphan*/  v_total_min; int /*<<< orphan*/  v_total_max; int /*<<< orphan*/  v_total; int /*<<< orphan*/  v_sync_a_pol; int /*<<< orphan*/  v_blank_end; int /*<<< orphan*/  v_blank_start; int /*<<< orphan*/  otg_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTC_INPUT_GLOBAL_CONTROL ; 
 int /*<<< orphan*/  OPTC_UNDERFLOW_OCCURRED_STATUS ; 
 int /*<<< orphan*/  OTG_CONTROL ; 
 int /*<<< orphan*/  OTG_H_BLANK_END ; 
 int /*<<< orphan*/  OTG_H_BLANK_START ; 
 int /*<<< orphan*/  OTG_H_BLANK_START_END ; 
 int /*<<< orphan*/  OTG_H_SYNC_A ; 
 int /*<<< orphan*/  OTG_H_SYNC_A_CNTL ; 
 int /*<<< orphan*/  OTG_H_SYNC_A_END ; 
 int /*<<< orphan*/  OTG_H_SYNC_A_POL ; 
 int /*<<< orphan*/  OTG_H_SYNC_A_START ; 
 int /*<<< orphan*/  OTG_H_TOTAL ; 
 int /*<<< orphan*/  OTG_MASTER_EN ; 
 int /*<<< orphan*/  OTG_V_BLANK_END ; 
 int /*<<< orphan*/  OTG_V_BLANK_START ; 
 int /*<<< orphan*/  OTG_V_BLANK_START_END ; 
 int /*<<< orphan*/  OTG_V_SYNC_A ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_CNTL ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_END ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_POL ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_START ; 
 int /*<<< orphan*/  OTG_V_TOTAL ; 
 int /*<<< orphan*/  OTG_V_TOTAL_CONTROL ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MAX ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MAX_SEL ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MIN ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MIN_SEL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void optc1_read_otg_state(struct optc *optc1,
		struct dcn_otg_state *s)
{
	REG_GET(OTG_CONTROL,
			OTG_MASTER_EN, &s->otg_enabled);

	REG_GET_2(OTG_V_BLANK_START_END,
			OTG_V_BLANK_START, &s->v_blank_start,
			OTG_V_BLANK_END, &s->v_blank_end);

	REG_GET(OTG_V_SYNC_A_CNTL,
			OTG_V_SYNC_A_POL, &s->v_sync_a_pol);

	REG_GET(OTG_V_TOTAL,
			OTG_V_TOTAL, &s->v_total);

	REG_GET(OTG_V_TOTAL_MAX,
			OTG_V_TOTAL_MAX, &s->v_total_max);

	REG_GET(OTG_V_TOTAL_MIN,
			OTG_V_TOTAL_MIN, &s->v_total_min);

	REG_GET(OTG_V_TOTAL_CONTROL,
			OTG_V_TOTAL_MAX_SEL, &s->v_total_max_sel);

	REG_GET(OTG_V_TOTAL_CONTROL,
			OTG_V_TOTAL_MIN_SEL, &s->v_total_min_sel);

	REG_GET_2(OTG_V_SYNC_A,
			OTG_V_SYNC_A_START, &s->v_sync_a_start,
			OTG_V_SYNC_A_END, &s->v_sync_a_end);

	REG_GET_2(OTG_H_BLANK_START_END,
			OTG_H_BLANK_START, &s->h_blank_start,
			OTG_H_BLANK_END, &s->h_blank_end);

	REG_GET_2(OTG_H_SYNC_A,
			OTG_H_SYNC_A_START, &s->h_sync_a_start,
			OTG_H_SYNC_A_END, &s->h_sync_a_end);

	REG_GET(OTG_H_SYNC_A_CNTL,
			OTG_H_SYNC_A_POL, &s->h_sync_a_pol);

	REG_GET(OTG_H_TOTAL,
			OTG_H_TOTAL, &s->h_total);

	REG_GET(OPTC_INPUT_GLOBAL_CONTROL,
			OPTC_UNDERFLOW_OCCURRED_STATUS, &s->underflow_occurred_status);
}