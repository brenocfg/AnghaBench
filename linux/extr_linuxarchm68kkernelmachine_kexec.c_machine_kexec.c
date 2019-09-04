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
struct kimage {int head; int /*<<< orphan*/  start; int /*<<< orphan*/  control_code_page; } ;
typedef  int /*<<< orphan*/  (* relocate_kernel_t ) (int,int /*<<< orphan*/ ,unsigned long) ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  __flush_cache_all () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int m68k_cputype ; 
 int m68k_mmutype ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relocate_new_kernel ; 
 int /*<<< orphan*/  relocate_new_kernel_size ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,unsigned long) ; 

void machine_kexec(struct kimage *image)
{
	void *reboot_code_buffer;
	unsigned long cpu_mmu_flags;

	reboot_code_buffer = page_address(image->control_code_page);

	memcpy(reboot_code_buffer, relocate_new_kernel,
	       relocate_new_kernel_size);

	/*
	 * we do not want to be bothered.
	 */
	local_irq_disable();

	pr_info("Will call new kernel at 0x%08lx. Bye...\n", image->start);
	__flush_cache_all();
	cpu_mmu_flags = m68k_cputype | m68k_mmutype << 8;
	((relocate_kernel_t) reboot_code_buffer)(image->head & PAGE_MASK,
						 image->start,
						 cpu_mmu_flags);
}