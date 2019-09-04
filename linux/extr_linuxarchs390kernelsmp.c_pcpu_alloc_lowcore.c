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
typedef  int /*<<< orphan*/  u32 ;
struct pcpu {struct lowcore* lowcore; } ;
struct lowcore {unsigned long async_stack; unsigned long panic_stack; int cpu_nr; int br_r1_trampoline; scalar_t__ spinlock_index; int /*<<< orphan*/  spinlock_lockval; } ;

/* Variables and functions */
 unsigned long ASYNC_FRAME_OFFSET ; 
 int /*<<< orphan*/  ASYNC_ORDER ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  LC_ORDER ; 
 unsigned long PANIC_FRAME_OFFSET ; 
 int /*<<< orphan*/  S390_lowcore ; 
 int /*<<< orphan*/  SIGP_SET_PREFIX ; 
 unsigned long __get_free_page (int) ; 
 unsigned long __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_spin_lockval (int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 struct lowcore** lowcore_ptr ; 
 int /*<<< orphan*/  memcpy (struct lowcore*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nmi_alloc_per_cpu (struct lowcore*) ; 
 int /*<<< orphan*/  nmi_free_per_cpu (struct lowcore*) ; 
 struct pcpu* pcpu_devices ; 
 int /*<<< orphan*/  pcpu_sigp_retry (struct pcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vdso_alloc_per_cpu (struct lowcore*) ; 

__attribute__((used)) static int pcpu_alloc_lowcore(struct pcpu *pcpu, int cpu)
{
	unsigned long async_stack, panic_stack;
	struct lowcore *lc;

	if (pcpu != &pcpu_devices[0]) {
		pcpu->lowcore =	(struct lowcore *)
			__get_free_pages(GFP_KERNEL | GFP_DMA, LC_ORDER);
		async_stack = __get_free_pages(GFP_KERNEL, ASYNC_ORDER);
		panic_stack = __get_free_page(GFP_KERNEL);
		if (!pcpu->lowcore || !panic_stack || !async_stack)
			goto out;
	} else {
		async_stack = pcpu->lowcore->async_stack - ASYNC_FRAME_OFFSET;
		panic_stack = pcpu->lowcore->panic_stack - PANIC_FRAME_OFFSET;
	}
	lc = pcpu->lowcore;
	memcpy(lc, &S390_lowcore, 512);
	memset((char *) lc + 512, 0, sizeof(*lc) - 512);
	lc->async_stack = async_stack + ASYNC_FRAME_OFFSET;
	lc->panic_stack = panic_stack + PANIC_FRAME_OFFSET;
	lc->cpu_nr = cpu;
	lc->spinlock_lockval = arch_spin_lockval(cpu);
	lc->spinlock_index = 0;
	lc->br_r1_trampoline = 0x07f1;	/* br %r1 */
	if (nmi_alloc_per_cpu(lc))
		goto out;
	if (vdso_alloc_per_cpu(lc))
		goto out_mcesa;
	lowcore_ptr[cpu] = lc;
	pcpu_sigp_retry(pcpu, SIGP_SET_PREFIX, (u32)(unsigned long) lc);
	return 0;

out_mcesa:
	nmi_free_per_cpu(lc);
out:
	if (pcpu != &pcpu_devices[0]) {
		free_page(panic_stack);
		free_pages(async_stack, ASYNC_ORDER);
		free_pages((unsigned long) pcpu->lowcore, LC_ORDER);
	}
	return -ENOMEM;
}