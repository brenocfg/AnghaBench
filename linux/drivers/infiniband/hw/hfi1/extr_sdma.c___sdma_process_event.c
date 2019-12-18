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
struct sdma_state {size_t current_state; int go_s99_running; int last_event; } ;
struct sdma_engine {TYPE_1__* dd; int /*<<< orphan*/  err_halt_worker; int /*<<< orphan*/  sdma_sw_clean_up_task; struct sdma_state state; int /*<<< orphan*/  this_idx; } ;
typedef  enum sdma_events { ____Placeholder_sdma_events } sdma_events ;
struct TYPE_2__ {int /*<<< orphan*/  sdma_unfreeze_wq; int /*<<< orphan*/  sdma_unfreeze_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dd_dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_err_progress_check_schedule (struct sdma_engine*) ; 
#define  sdma_event_e00_go_hw_down 152 
#define  sdma_event_e10_go_hw_start 151 
#define  sdma_event_e15_hw_halt_done 150 
#define  sdma_event_e25_hw_clean_up_done 149 
#define  sdma_event_e30_go_running 148 
#define  sdma_event_e40_sw_cleaned 147 
#define  sdma_event_e50_hw_cleaned 146 
#define  sdma_event_e60_hw_halted 145 
#define  sdma_event_e70_go_idle 144 
#define  sdma_event_e80_hw_freeze 143 
#define  sdma_event_e81_hw_frozen 142 
#define  sdma_event_e82_hw_unfreeze 141 
#define  sdma_event_e85_link_down 140 
#define  sdma_event_e90_sw_halted 139 
 int /*<<< orphan*/ * sdma_event_names ; 
 int /*<<< orphan*/  sdma_get (struct sdma_state*) ; 
 int /*<<< orphan*/  sdma_hw_start_up (struct sdma_engine*) ; 
 int /*<<< orphan*/  sdma_make_progress (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_set_state (struct sdma_engine*,int const) ; 
 int /*<<< orphan*/  sdma_start_hw_clean_up (struct sdma_engine*) ; 
 int /*<<< orphan*/ * sdma_state_names ; 
#define  sdma_state_s00_hw_down 138 
#define  sdma_state_s10_hw_start_up_halt_wait 137 
#define  sdma_state_s15_hw_start_up_clean_wait 136 
#define  sdma_state_s20_idle 135 
#define  sdma_state_s30_sw_clean_up_wait 134 
#define  sdma_state_s40_hw_clean_up_wait 133 
#define  sdma_state_s50_hw_halt_wait 132 
#define  sdma_state_s60_idle_halt_wait 131 
#define  sdma_state_s80_hw_freeze 130 
#define  sdma_state_s82_freeze_sw_clean 129 
#define  sdma_state_s99_running 128 
 int /*<<< orphan*/  sdma_sw_tear_down (struct sdma_engine*) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __sdma_process_event(struct sdma_engine *sde,
				 enum sdma_events event)
{
	struct sdma_state *ss = &sde->state;
	int need_progress = 0;

	/* CONFIG SDMA temporary */
#ifdef CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) [%s] %s\n", sde->this_idx,
		   sdma_state_names[ss->current_state],
		   sdma_event_names[event]);
#endif

	switch (ss->current_state) {
	case sdma_state_s00_hw_down:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			break;
		case sdma_event_e30_go_running:
			/*
			 * If down, but running requested (usually result
			 * of link up, then we need to start up.
			 * This can happen when hw down is requested while
			 * bringing the link up with traffic active on
			 * 7220, e.g.
			 */
			ss->go_s99_running = 1;
			/* fall through -- and start dma engine */
		case sdma_event_e10_go_hw_start:
			/* This reference means the state machine is started */
			sdma_get(&sde->state);
			sdma_set_state(sde,
				       sdma_state_s10_hw_start_up_halt_wait);
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e40_sw_cleaned:
			sdma_sw_tear_down(sde);
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s10_hw_start_up_halt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_tear_down(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			sdma_set_state(sde,
				       sdma_state_s15_hw_start_up_clean_wait);
			sdma_start_hw_clean_up(sde);
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			schedule_work(&sde->err_halt_worker);
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s15_hw_start_up_clean_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_tear_down(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s20_idle:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_tear_down(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			sdma_set_state(sde, sdma_state_s99_running);
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			sdma_set_state(sde, sdma_state_s50_hw_halt_wait);
			schedule_work(&sde->err_halt_worker);
			break;
		case sdma_event_e70_go_idle:
			break;
		case sdma_event_e85_link_down:
			/* fall through */
		case sdma_event_e80_hw_freeze:
			sdma_set_state(sde, sdma_state_s80_hw_freeze);
			atomic_dec(&sde->dd->sdma_unfreeze_count);
			wake_up_interruptible(&sde->dd->sdma_unfreeze_wq);
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s30_sw_clean_up_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			sdma_set_state(sde, sdma_state_s40_hw_clean_up_wait);
			sdma_start_hw_clean_up(sde);
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s40_hw_clean_up_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s50_hw_halt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			sdma_set_state(sde, sdma_state_s30_sw_clean_up_wait);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			schedule_work(&sde->err_halt_worker);
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s60_idle_halt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			sdma_set_state(sde, sdma_state_s30_sw_clean_up_wait);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			schedule_work(&sde->err_halt_worker);
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s80_hw_freeze:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			sdma_set_state(sde, sdma_state_s82_freeze_sw_clean);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s82_freeze_sw_clean:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			/* notify caller this engine is done cleaning */
			atomic_dec(&sde->dd->sdma_unfreeze_count);
			wake_up_interruptible(&sde->dd->sdma_unfreeze_wq);
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s99_running:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			tasklet_hi_schedule(&sde->sdma_sw_clean_up_task);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			need_progress = 1;
			sdma_err_progress_check_schedule(sde);
			/* fall through */
		case sdma_event_e90_sw_halted:
			/*
			* SW initiated halt does not perform engines
			* progress check
			*/
			sdma_set_state(sde, sdma_state_s50_hw_halt_wait);
			schedule_work(&sde->err_halt_worker);
			break;
		case sdma_event_e70_go_idle:
			sdma_set_state(sde, sdma_state_s60_idle_halt_wait);
			break;
		case sdma_event_e85_link_down:
			ss->go_s99_running = 0;
			/* fall through */
		case sdma_event_e80_hw_freeze:
			sdma_set_state(sde, sdma_state_s80_hw_freeze);
			atomic_dec(&sde->dd->sdma_unfreeze_count);
			wake_up_interruptible(&sde->dd->sdma_unfreeze_wq);
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		}
		break;
	}

	ss->last_event = event;
	if (need_progress)
		sdma_make_progress(sde, 0);
}