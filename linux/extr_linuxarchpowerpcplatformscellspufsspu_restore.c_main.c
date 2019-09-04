#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void** ui; } ;
typedef  TYPE_1__ addr64 ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_RdSigNotify1 ; 
 int /*<<< orphan*/  SPU_RdSigNotify2 ; 
 int /*<<< orphan*/  build_dma_list (TYPE_1__) ; 
 int /*<<< orphan*/  enqueue_putllc (TYPE_1__) ; 
 int /*<<< orphan*/  fetch_regs_from_mem (TYPE_1__) ; 
 int /*<<< orphan*/  read_llar_status () ; 
 int /*<<< orphan*/  read_tag_status () ; 
 int /*<<< orphan*/  restore_complete () ; 
 int /*<<< orphan*/  restore_decr () ; 
 int /*<<< orphan*/  restore_event_mask () ; 
 int /*<<< orphan*/  restore_fpcr () ; 
 int /*<<< orphan*/  restore_srr0 () ; 
 int /*<<< orphan*/  restore_tag_mask () ; 
 int /*<<< orphan*/  restore_upper_240kb (TYPE_1__) ; 
 int /*<<< orphan*/  set_event_mask () ; 
 int /*<<< orphan*/  set_tag_mask () ; 
 int /*<<< orphan*/  set_tag_update () ; 
 void* spu_readch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_ppu_mb () ; 
 int /*<<< orphan*/  write_ppuint_mb () ; 

int main()
{
	addr64 lscsa_ea;

	lscsa_ea.ui[0] = spu_readch(SPU_RdSigNotify1);
	lscsa_ea.ui[1] = spu_readch(SPU_RdSigNotify2);
	fetch_regs_from_mem(lscsa_ea);

	set_event_mask();		/* Step 1.  */
	set_tag_mask();			/* Step 2.  */
	build_dma_list(lscsa_ea);	/* Step 3.  */
	restore_upper_240kb(lscsa_ea);	/* Step 4.  */
					/* Step 5: done by 'exit'. */
	enqueue_putllc(lscsa_ea);	/* Step 7. */
	set_tag_update();		/* Step 8. */
	read_tag_status();		/* Step 9. */
	restore_decr();			/* moved Step 6. */
	read_llar_status();		/* Step 10. */
	write_ppu_mb();			/* Step 11. */
	write_ppuint_mb();		/* Step 12. */
	restore_fpcr();			/* Step 13. */
	restore_srr0();			/* Step 14. */
	restore_event_mask();		/* Step 15. */
	restore_tag_mask();		/* Step 16. */
					/* Step 17. done by 'exit'. */
	restore_complete();		/* Step 18. */

	return 0;
}