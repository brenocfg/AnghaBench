#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void** ui; } ;
typedef  TYPE_1__ addr64 ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_RdSigNotify1 ; 
 int /*<<< orphan*/  SPU_RdSigNotify2 ; 
 int /*<<< orphan*/  build_dma_list (TYPE_1__) ; 
 int /*<<< orphan*/  enqueue_putllc (TYPE_1__) ; 
 int /*<<< orphan*/  enqueue_sync (TYPE_1__) ; 
 int /*<<< orphan*/  read_llar_status () ; 
 int /*<<< orphan*/  read_tag_status () ; 
 int /*<<< orphan*/  save_complete () ; 
 int /*<<< orphan*/  save_decr () ; 
 int /*<<< orphan*/  save_event_mask () ; 
 int /*<<< orphan*/  save_fpcr () ; 
 int /*<<< orphan*/  save_srr0 () ; 
 int /*<<< orphan*/  save_tag_mask () ; 
 int /*<<< orphan*/  save_upper_240kb (TYPE_1__) ; 
 int /*<<< orphan*/  set_event_mask () ; 
 int /*<<< orphan*/  set_tag_mask () ; 
 int /*<<< orphan*/  set_tag_update () ; 
 int /*<<< orphan*/  spill_regs_to_mem (TYPE_1__) ; 
 void* spu_readch (int /*<<< orphan*/ ) ; 

int main()
{
	addr64 lscsa_ea;

	lscsa_ea.ui[0] = spu_readch(SPU_RdSigNotify1);
	lscsa_ea.ui[1] = spu_readch(SPU_RdSigNotify2);

	/* Step 1: done by exit(). */
	save_event_mask();	/* Step 2.  */
	save_tag_mask();	/* Step 3.  */
	set_event_mask();	/* Step 4.  */
	set_tag_mask();		/* Step 5.  */
	build_dma_list(lscsa_ea);	/* Step 6.  */
	save_upper_240kb(lscsa_ea);	/* Step 7.  */
	/* Step 8: done by exit(). */
	save_fpcr();		/* Step 9.  */
	save_decr();		/* Step 10. */
	save_srr0();		/* Step 11. */
	enqueue_putllc(lscsa_ea);	/* Step 12. */
	spill_regs_to_mem(lscsa_ea);	/* Step 13. */
	enqueue_sync(lscsa_ea);	/* Step 14. */
	set_tag_update();	/* Step 15. */
	read_tag_status();	/* Step 16. */
	read_llar_status();	/* Step 17. */
	save_complete();	/* Step 18. */

	return 0;
}