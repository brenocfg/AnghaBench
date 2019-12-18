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
struct qib_sdma_state {int current_state; int go_s99_running; int last_event; } ;
struct qib_pportdata {TYPE_1__* dd; struct qib_sdma_state sdma_state; } ;
typedef  enum qib_sdma_events { ____Placeholder_qib_sdma_events } qib_sdma_events ;
struct TYPE_2__ {int /*<<< orphan*/  (* f_sdma_hw_clean_up ) (struct qib_pportdata*) ;} ;

/* Variables and functions */
#define  qib_sdma_event_e00_go_hw_down 145 
#define  qib_sdma_event_e10_go_hw_start 144 
#define  qib_sdma_event_e20_hw_started 143 
#define  qib_sdma_event_e30_go_running 142 
#define  qib_sdma_event_e40_sw_cleaned 141 
#define  qib_sdma_event_e50_hw_cleaned 140 
#define  qib_sdma_event_e60_hw_halted 139 
#define  qib_sdma_event_e70_go_idle 138 
#define  qib_sdma_event_e7220_err_halted 137 
#define  qib_sdma_event_e7322_err_halted 136 
#define  qib_sdma_event_e90_timer_tick 135 
#define  qib_sdma_state_s00_hw_down 134 
#define  qib_sdma_state_s10_hw_start_up_wait 133 
#define  qib_sdma_state_s20_idle 132 
#define  qib_sdma_state_s30_sw_clean_up_wait 131 
#define  qib_sdma_state_s40_hw_clean_up_wait 130 
#define  qib_sdma_state_s50_hw_halt_wait 129 
#define  qib_sdma_state_s99_running 128 
 int /*<<< orphan*/  sdma_get (struct qib_sdma_state*) ; 
 int /*<<< orphan*/  sdma_hw_start_up (struct qib_pportdata*) ; 
 int /*<<< orphan*/  sdma_set_state (struct qib_pportdata*,int const) ; 
 int /*<<< orphan*/  sdma_start_sw_clean_up (struct qib_pportdata*) ; 
 int /*<<< orphan*/  sdma_sw_tear_down (struct qib_pportdata*) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*) ; 

void __qib_sdma_process_event(struct qib_pportdata *ppd,
	enum qib_sdma_events event)
{
	struct qib_sdma_state *ss = &ppd->sdma_state;

	switch (ss->current_state) {
	case qib_sdma_state_s00_hw_down:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			break;
		case qib_sdma_event_e30_go_running:
			/*
			 * If down, but running requested (usually result
			 * of link up, then we need to start up.
			 * This can happen when hw down is requested while
			 * bringing the link up with traffic active on
			 * 7220, e.g. */
			ss->go_s99_running = 1;
			/* fall through -- and start dma engine */
		case qib_sdma_event_e10_go_hw_start:
			/* This reference means the state machine is started */
			sdma_get(&ppd->sdma_state);
			sdma_set_state(ppd,
				       qib_sdma_state_s10_hw_start_up_wait);
			break;
		case qib_sdma_event_e20_hw_started:
			break;
		case qib_sdma_event_e40_sw_cleaned:
			sdma_sw_tear_down(ppd);
			break;
		case qib_sdma_event_e50_hw_cleaned:
			break;
		case qib_sdma_event_e60_hw_halted:
			break;
		case qib_sdma_event_e70_go_idle:
			break;
		case qib_sdma_event_e7220_err_halted:
			break;
		case qib_sdma_event_e7322_err_halted:
			break;
		case qib_sdma_event_e90_timer_tick:
			break;
		}
		break;

	case qib_sdma_state_s10_hw_start_up_wait:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_sw_tear_down(ppd);
			break;
		case qib_sdma_event_e10_go_hw_start:
			break;
		case qib_sdma_event_e20_hw_started:
			sdma_set_state(ppd, ss->go_s99_running ?
				       qib_sdma_state_s99_running :
				       qib_sdma_state_s20_idle);
			break;
		case qib_sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case qib_sdma_event_e40_sw_cleaned:
			break;
		case qib_sdma_event_e50_hw_cleaned:
			break;
		case qib_sdma_event_e60_hw_halted:
			break;
		case qib_sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case qib_sdma_event_e7220_err_halted:
			break;
		case qib_sdma_event_e7322_err_halted:
			break;
		case qib_sdma_event_e90_timer_tick:
			break;
		}
		break;

	case qib_sdma_state_s20_idle:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_sw_tear_down(ppd);
			break;
		case qib_sdma_event_e10_go_hw_start:
			break;
		case qib_sdma_event_e20_hw_started:
			break;
		case qib_sdma_event_e30_go_running:
			sdma_set_state(ppd, qib_sdma_state_s99_running);
			ss->go_s99_running = 1;
			break;
		case qib_sdma_event_e40_sw_cleaned:
			break;
		case qib_sdma_event_e50_hw_cleaned:
			break;
		case qib_sdma_event_e60_hw_halted:
			break;
		case qib_sdma_event_e70_go_idle:
			break;
		case qib_sdma_event_e7220_err_halted:
			break;
		case qib_sdma_event_e7322_err_halted:
			break;
		case qib_sdma_event_e90_timer_tick:
			break;
		}
		break;

	case qib_sdma_state_s30_sw_clean_up_wait:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			break;
		case qib_sdma_event_e10_go_hw_start:
			break;
		case qib_sdma_event_e20_hw_started:
			break;
		case qib_sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case qib_sdma_event_e40_sw_cleaned:
			sdma_set_state(ppd,
				       qib_sdma_state_s10_hw_start_up_wait);
			sdma_hw_start_up(ppd);
			break;
		case qib_sdma_event_e50_hw_cleaned:
			break;
		case qib_sdma_event_e60_hw_halted:
			break;
		case qib_sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case qib_sdma_event_e7220_err_halted:
			break;
		case qib_sdma_event_e7322_err_halted:
			break;
		case qib_sdma_event_e90_timer_tick:
			break;
		}
		break;

	case qib_sdma_state_s40_hw_clean_up_wait:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(ppd);
			break;
		case qib_sdma_event_e10_go_hw_start:
			break;
		case qib_sdma_event_e20_hw_started:
			break;
		case qib_sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case qib_sdma_event_e40_sw_cleaned:
			break;
		case qib_sdma_event_e50_hw_cleaned:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_clean_up_wait);
			sdma_start_sw_clean_up(ppd);
			break;
		case qib_sdma_event_e60_hw_halted:
			break;
		case qib_sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case qib_sdma_event_e7220_err_halted:
			break;
		case qib_sdma_event_e7322_err_halted:
			break;
		case qib_sdma_event_e90_timer_tick:
			break;
		}
		break;

	case qib_sdma_state_s50_hw_halt_wait:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(ppd);
			break;
		case qib_sdma_event_e10_go_hw_start:
			break;
		case qib_sdma_event_e20_hw_started:
			break;
		case qib_sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case qib_sdma_event_e40_sw_cleaned:
			break;
		case qib_sdma_event_e50_hw_cleaned:
			break;
		case qib_sdma_event_e60_hw_halted:
			sdma_set_state(ppd,
				       qib_sdma_state_s40_hw_clean_up_wait);
			ppd->dd->f_sdma_hw_clean_up(ppd);
			break;
		case qib_sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case qib_sdma_event_e7220_err_halted:
			break;
		case qib_sdma_event_e7322_err_halted:
			break;
		case qib_sdma_event_e90_timer_tick:
			break;
		}
		break;

	case qib_sdma_state_s99_running:
		switch (event) {
		case qib_sdma_event_e00_go_hw_down:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(ppd);
			break;
		case qib_sdma_event_e10_go_hw_start:
			break;
		case qib_sdma_event_e20_hw_started:
			break;
		case qib_sdma_event_e30_go_running:
			break;
		case qib_sdma_event_e40_sw_cleaned:
			break;
		case qib_sdma_event_e50_hw_cleaned:
			break;
		case qib_sdma_event_e60_hw_halted:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_clean_up_wait);
			sdma_start_sw_clean_up(ppd);
			break;
		case qib_sdma_event_e70_go_idle:
			sdma_set_state(ppd, qib_sdma_state_s50_hw_halt_wait);
			ss->go_s99_running = 0;
			break;
		case qib_sdma_event_e7220_err_halted:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_clean_up_wait);
			sdma_start_sw_clean_up(ppd);
			break;
		case qib_sdma_event_e7322_err_halted:
			sdma_set_state(ppd, qib_sdma_state_s50_hw_halt_wait);
			break;
		case qib_sdma_event_e90_timer_tick:
			break;
		}
		break;
	}

	ss->last_event = event;
}