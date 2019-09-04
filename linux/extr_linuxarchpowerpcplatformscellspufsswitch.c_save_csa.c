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
 int /*<<< orphan*/  purge_mfc_queue (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reset_ch (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reset_spu_lslr (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reset_spu_privcntl (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_ch_part1 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_cmd (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_csr_ato (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_csr_cmd (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_csr_tsq (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_queues (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_rag (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_tclass_id (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_pm_trace (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_ppu_mb (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_ppu_mb_stat (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_ppu_querymask (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_ppu_querytype (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_ppu_tagstatus (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_ppuint_mb (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_spu_cfg (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_spu_lslr (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_spu_mb (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_spu_npc (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_spu_privcntl (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  set_mfc_tclass_id (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  setup_mfc_sr1 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  wait_purge_complete (struct spu_state*,struct spu*) ; 

__attribute__((used)) static void save_csa(struct spu_state *prev, struct spu *spu)
{
	/*
	 * Combine steps 19-44 of SPU context save sequence, which
	 * save regions of the privileged & problem state areas.
	 */

	save_mfc_queues(prev, spu);	/* Step 19. */
	save_ppu_querymask(prev, spu);	/* Step 20. */
	save_ppu_querytype(prev, spu);	/* Step 21. */
	save_ppu_tagstatus(prev, spu);  /* NEW.     */
	save_mfc_csr_tsq(prev, spu);	/* Step 22. */
	save_mfc_csr_cmd(prev, spu);	/* Step 23. */
	save_mfc_csr_ato(prev, spu);	/* Step 24. */
	save_mfc_tclass_id(prev, spu);	/* Step 25. */
	set_mfc_tclass_id(prev, spu);	/* Step 26. */
	save_mfc_cmd(prev, spu);	/* Step 26a - moved from 44. */
	purge_mfc_queue(prev, spu);	/* Step 27. */
	wait_purge_complete(prev, spu);	/* Step 28. */
	setup_mfc_sr1(prev, spu);	/* Step 30. */
	save_spu_npc(prev, spu);	/* Step 31. */
	save_spu_privcntl(prev, spu);	/* Step 32. */
	reset_spu_privcntl(prev, spu);	/* Step 33. */
	save_spu_lslr(prev, spu);	/* Step 34. */
	reset_spu_lslr(prev, spu);	/* Step 35. */
	save_spu_cfg(prev, spu);	/* Step 36. */
	save_pm_trace(prev, spu);	/* Step 37. */
	save_mfc_rag(prev, spu);	/* Step 38. */
	save_ppu_mb_stat(prev, spu);	/* Step 39. */
	save_ppu_mb(prev, spu);	        /* Step 40. */
	save_ppuint_mb(prev, spu);	/* Step 41. */
	save_ch_part1(prev, spu);	/* Step 42. */
	save_spu_mb(prev, spu);	        /* Step 43. */
	reset_ch(prev, spu);	        /* Step 45. */
}