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
struct swap_insn_args {int /*<<< orphan*/  arm_kprobe; struct kprobe* p; } ;
struct kprobe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stop_machine_cpuslocked (int /*<<< orphan*/ ,struct swap_insn_args*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_instruction ; 

void arch_disarm_kprobe(struct kprobe *p)
{
	struct swap_insn_args args = {.p = p, .arm_kprobe = 0};

	stop_machine_cpuslocked(swap_instruction, &args, NULL);
}