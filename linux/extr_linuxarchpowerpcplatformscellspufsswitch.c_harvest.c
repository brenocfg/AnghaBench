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
struct spu_state {int dummy; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_spu_status (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  disable_interrupts (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  do_mfc_mssync (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  enable_interrupts (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  handle_pending_interrupts (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  inhibit_user_access (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  issue_mfc_tlbie (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  purge_mfc_queue (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  remove_other_spu_access (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reset_ch_part1 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reset_ch_part2 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reset_spu_lslr (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reset_spu_privcntl (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  resume_mfc_queue (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  set_mfc_tclass_id (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  set_switch_active (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  set_switch_pending (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  setup_mfc_sr1 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  spu_invalidate_slbs (struct spu*) ; 
 int /*<<< orphan*/  stop_spu_isolate (struct spu*) ; 
 int /*<<< orphan*/  suspend_mfc_and_halt_decr (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  suspend_spe (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  terminate_spu_app (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  wait_purge_complete (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  wait_suspend_mfc_complete (struct spu_state*,struct spu*) ; 

__attribute__((used)) static void harvest(struct spu_state *prev, struct spu *spu)
{
	/*
	 * Perform steps 2-25 of SPU context restore sequence,
	 * which resets an SPU either after a failed save, or
	 * when using SPU for first time.
	 */

	disable_interrupts(prev, spu);	        /* Step 2.  */
	inhibit_user_access(prev, spu);	        /* Step 3.  */
	terminate_spu_app(prev, spu);	        /* Step 4.  */
	set_switch_pending(prev, spu);	        /* Step 5.  */
	stop_spu_isolate(spu);			/* NEW.     */
	remove_other_spu_access(prev, spu);	/* Step 6.  */
	suspend_mfc_and_halt_decr(prev, spu);	/* Step 7.  */
	wait_suspend_mfc_complete(prev, spu);	/* Step 8.  */
	if (!suspend_spe(prev, spu))	        /* Step 9.  */
		clear_spu_status(prev, spu);	/* Step 10. */
	do_mfc_mssync(prev, spu);	        /* Step 11. */
	issue_mfc_tlbie(prev, spu);	        /* Step 12. */
	handle_pending_interrupts(prev, spu);	/* Step 13. */
	purge_mfc_queue(prev, spu);	        /* Step 14. */
	wait_purge_complete(prev, spu);	        /* Step 15. */
	reset_spu_privcntl(prev, spu);	        /* Step 16. */
	reset_spu_lslr(prev, spu);              /* Step 17. */
	setup_mfc_sr1(prev, spu);	        /* Step 18. */
	spu_invalidate_slbs(spu);		/* Step 19. */
	reset_ch_part1(prev, spu);	        /* Step 20. */
	reset_ch_part2(prev, spu);	        /* Step 21. */
	enable_interrupts(prev, spu);	        /* Step 22. */
	set_switch_active(prev, spu);	        /* Step 23. */
	set_mfc_tclass_id(prev, spu);	        /* Step 24. */
	resume_mfc_queue(prev, spu);	        /* Step 25. */
}