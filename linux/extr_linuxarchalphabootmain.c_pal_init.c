#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct percpu_struct {unsigned long pal_revision; unsigned long* palcode_avail; } ;
struct pcb_struct {int dummy; } ;
struct TYPE_6__ {scalar_t__ processor_offset; } ;
struct TYPE_5__ {int ptbr; int flags; scalar_t__ res2; scalar_t__ res1; scalar_t__ unique; scalar_t__ pcc; scalar_t__ asn; scalar_t__ usp; scalar_t__ ksp; } ;

/* Variables and functions */
 TYPE_4__* INIT_HWRPB ; 
 int* L1 ; 
 int /*<<< orphan*/  VPTB ; 
 int /*<<< orphan*/  __halt () ; 
 struct pcb_struct* find_pa (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* pcb_va ; 
 int /*<<< orphan*/  srm_printk (char*,...) ; 
 unsigned long switch_to_osf_pal (int,TYPE_1__*,struct pcb_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbia () ; 

void
pal_init(void)
{
	unsigned long i, rev;
	struct percpu_struct * percpu;
	struct pcb_struct * pcb_pa;

	/* Create the dummy PCB.  */
	pcb_va->ksp = 0;
	pcb_va->usp = 0;
	pcb_va->ptbr = L1[1] >> 32;
	pcb_va->asn = 0;
	pcb_va->pcc = 0;
	pcb_va->unique = 0;
	pcb_va->flags = 1;
	pcb_va->res1 = 0;
	pcb_va->res2 = 0;
	pcb_pa = find_pa(VPTB, pcb_va);

	/*
	 * a0 = 2 (OSF)
	 * a1 = return address, but we give the asm the vaddr of the PCB
	 * a2 = physical addr of PCB
	 * a3 = new virtual page table pointer
	 * a4 = KSP (but the asm sets it)
	 */
	srm_printk("Switching to OSF PAL-code .. ");

	i = switch_to_osf_pal(2, pcb_va, pcb_pa, VPTB);
	if (i) {
		srm_printk("failed, code %ld\n", i);
		__halt();
	}

	percpu = (struct percpu_struct *)
		(INIT_HWRPB->processor_offset + (unsigned long) INIT_HWRPB);
	rev = percpu->pal_revision = percpu->palcode_avail[2];

	srm_printk("Ok (rev %lx)\n", rev);

	tbia(); /* do it directly in case we are SMP */
}