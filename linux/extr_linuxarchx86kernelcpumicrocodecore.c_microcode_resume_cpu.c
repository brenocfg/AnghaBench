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
typedef  enum ucode_state { ____Placeholder_ucode_state } ucode_state ;

/* Variables and functions */
 int UCODE_ERROR ; 
 int UCODE_OK ; 
 scalar_t__ apply_microcode_on_target (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static enum ucode_state microcode_resume_cpu(int cpu)
{
	if (apply_microcode_on_target(cpu))
		return UCODE_ERROR;

	pr_debug("CPU%d updated upon resume\n", cpu);

	return UCODE_OK;
}