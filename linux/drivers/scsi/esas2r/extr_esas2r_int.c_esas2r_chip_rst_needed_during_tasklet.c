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
struct esas2r_adapter {scalar_t__ chip_uptime; scalar_t__ int_mask; int /*<<< orphan*/  prev_dev_cnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  chip_init_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BUSRST_DETECTED ; 
 int /*<<< orphan*/  AF_BUSRST_NEEDED ; 
 int /*<<< orphan*/  AF_BUSRST_PENDING ; 
 int /*<<< orphan*/  AF_CHPRST_NEEDED ; 
 int /*<<< orphan*/  AF_CHPRST_PENDING ; 
 int /*<<< orphan*/  AF_CHPRST_STARTED ; 
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  AF_DISABLED ; 
 int /*<<< orphan*/  AF_DISC_PENDING ; 
 int /*<<< orphan*/  AF_FIRST_INIT ; 
 int /*<<< orphan*/  AF_POWER_MGT ; 
 scalar_t__ ESAS2R_CHP_UPTIME_CNT ; 
 scalar_t__ ESAS2R_CHP_UPTIME_MAX ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_disable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int /*<<< orphan*/  esas2r_is_adapter_present (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esas2r_process_adapter_reset (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_reset_chip (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_targ_db_get_tgt_cnt (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_targ_db_remove_all (struct esas2r_adapter*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esas2r_chip_rst_needed_during_tasklet(struct esas2r_adapter *a)
{

	clear_bit(AF_CHPRST_NEEDED, &a->flags);
	clear_bit(AF_BUSRST_NEEDED, &a->flags);
	clear_bit(AF_BUSRST_DETECTED, &a->flags);
	clear_bit(AF_BUSRST_PENDING, &a->flags);
	/*
	 * Make sure we don't get attempt more than 3 resets
	 * when the uptime between resets does not exceed one
	 * minute.  This will stop any situation where there is
	 * really something wrong with the hardware.  The way
	 * this works is that we start with uptime ticks at 0.
	 * Each time we do a reset, we add 20 seconds worth to
	 * the count.  Each time a timer tick occurs, as long
	 * as a chip reset is not pending, we decrement the
	 * tick count.  If the uptime ticks ever gets to 60
	 * seconds worth, we disable the adapter from that
	 * point forward.  Three strikes, you're out.
	 */
	if (!esas2r_is_adapter_present(a) || (a->chip_uptime >=
					      ESAS2R_CHP_UPTIME_MAX)) {
		esas2r_hdebug("*** adapter disabled ***");

		/*
		 * Ok, some kind of hard failure.  Make sure we
		 * exit this loop with chip interrupts
		 * permanently disabled so we don't lock up the
		 * entire system.  Also flag degraded mode to
		 * prevent the heartbeat from trying to recover.
		 */

		set_bit(AF_DEGRADED_MODE, &a->flags);
		set_bit(AF_DISABLED, &a->flags);
		clear_bit(AF_CHPRST_PENDING, &a->flags);
		clear_bit(AF_DISC_PENDING, &a->flags);

		esas2r_disable_chip_interrupts(a);
		a->int_mask = 0;
		esas2r_process_adapter_reset(a);

		esas2r_log(ESAS2R_LOG_CRIT,
			   "Adapter disabled because of hardware failure");
	} else {
		bool alrdyrst = test_and_set_bit(AF_CHPRST_STARTED, &a->flags);

		if (!alrdyrst)
			/*
			 * Only disable interrupts if this is
			 * the first reset attempt.
			 */
			esas2r_disable_chip_interrupts(a);

		if ((test_bit(AF_POWER_MGT, &a->flags)) &&
		    !test_bit(AF_FIRST_INIT, &a->flags) && !alrdyrst) {
			/*
			 * Don't reset the chip on the first
			 * deferred power up attempt.
			 */
		} else {
			esas2r_hdebug("*** resetting chip ***");
			esas2r_reset_chip(a);
		}

		/* Kick off the reinitialization */
		a->chip_uptime += ESAS2R_CHP_UPTIME_CNT;
		a->chip_init_time = jiffies_to_msecs(jiffies);
		if (!test_bit(AF_POWER_MGT, &a->flags)) {
			esas2r_process_adapter_reset(a);

			if (!alrdyrst) {
				/* Remove devices now that I/O is cleaned up. */
				a->prev_dev_cnt =
					esas2r_targ_db_get_tgt_cnt(a);
				esas2r_targ_db_remove_all(a, false);
			}
		}

		a->int_mask = 0;
	}
}