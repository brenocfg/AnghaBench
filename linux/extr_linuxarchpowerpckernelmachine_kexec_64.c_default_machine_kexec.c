#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct paca_struct {int dummy; } ;
struct kimage {int /*<<< orphan*/  control_code_page; int /*<<< orphan*/  start; } ;
struct TYPE_12__ {int /*<<< orphan*/  cpu; int /*<<< orphan*/  task; } ;
struct TYPE_9__ {int /*<<< orphan*/  cpu; int /*<<< orphan*/  preempt_count; scalar_t__ flags; int /*<<< orphan*/  task; } ;
struct TYPE_11__ {TYPE_1__ thread_info; } ;
struct TYPE_10__ {int data_offset; size_t paca_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int /*<<< orphan*/  FW_FEATURE_PS3_LV1 ; 
 int /*<<< orphan*/  HARDIRQ_OFFSET ; 
 TYPE_8__* current_thread_info () ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_paca () ; 
 int /*<<< orphan*/  kdump_in_progress () ; 
 TYPE_2__ kexec_paca ; 
 int /*<<< orphan*/  kexec_prepare_cpus () ; 
 int /*<<< orphan*/  kexec_sequence (TYPE_5__*,int /*<<< orphan*/ ,struct kimage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ kexec_stack ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmu_cleanup_all ; 
 TYPE_2__** paca_ptrs ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  setup_paca (TYPE_2__*) ; 

void default_machine_kexec(struct kimage *image)
{
	bool copy_with_mmu_off;

	/* prepare control code if any */

	/*
        * If the kexec boot is the normal one, need to shutdown other cpus
        * into our wait loop and quiesce interrupts.
        * Otherwise, in the case of crashed mode (crashing_cpu >= 0),
        * stopping other CPUs and collecting their pt_regs is done before
        * using debugger IPI.
        */

	if (!kdump_in_progress())
		kexec_prepare_cpus();

	printk("kexec: Starting switchover sequence.\n");

	/* switch to a staticly allocated stack.  Based on irq stack code.
	 * We setup preempt_count to avoid using VMX in memcpy.
	 * XXX: the task struct will likely be invalid once we do the copy!
	 */
	kexec_stack.thread_info.task = current_thread_info()->task;
	kexec_stack.thread_info.flags = 0;
	kexec_stack.thread_info.preempt_count = HARDIRQ_OFFSET;
	kexec_stack.thread_info.cpu = current_thread_info()->cpu;

	/* We need a static PACA, too; copy this CPU's PACA over and switch to
	 * it. Also poison per_cpu_offset and NULL lppaca to catch anyone using
	 * non-static data.
	 */
	memcpy(&kexec_paca, get_paca(), sizeof(struct paca_struct));
	kexec_paca.data_offset = 0xedeaddeadeeeeeeeUL;
#ifdef CONFIG_PPC_PSERIES
	kexec_paca.lppaca_ptr = NULL;
#endif
	paca_ptrs[kexec_paca.paca_index] = &kexec_paca;

	setup_paca(&kexec_paca);

	/*
	 * The lppaca should be unregistered at this point so the HV won't
	 * touch it. In the case of a crash, none of the lppacas are
	 * unregistered so there is not much we can do about it here.
	 */

	/*
	 * On Book3S, the copy must happen with the MMU off if we are either
	 * using Radix page tables or we are not in an LPAR since we can
	 * overwrite the page tables while copying.
	 *
	 * In an LPAR, we keep the MMU on otherwise we can't access beyond
	 * the RMA. On BookE there is no real MMU off mode, so we have to
	 * keep it enabled as well (but then we have bolted TLB entries).
	 */
#ifdef CONFIG_PPC_BOOK3E
	copy_with_mmu_off = false;
#else
	copy_with_mmu_off = radix_enabled() ||
		!(firmware_has_feature(FW_FEATURE_LPAR) ||
		  firmware_has_feature(FW_FEATURE_PS3_LV1));
#endif

	/* Some things are best done in assembly.  Finding globals with
	 * a toc is easier in C, so pass in what we can.
	 */
	kexec_sequence(&kexec_stack, image->start, image,
		       page_address(image->control_code_page),
		       mmu_cleanup_all, copy_with_mmu_off);
	/* NOTREACHED */
}