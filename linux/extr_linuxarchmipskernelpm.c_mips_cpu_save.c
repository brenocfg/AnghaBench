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

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lose_fpu (int) ; 
 int /*<<< orphan*/  save_dsp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mips_cpu_save(void)
{
	/* Save FPU state */
	lose_fpu(1);

	/* Save DSP state */
	save_dsp(current);

	return 0;
}