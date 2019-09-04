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

/* Variables and functions */
 int /*<<< orphan*/  ST0_MX ; 
 scalar_t__ cpu_has_dsp ; 
 int /*<<< orphan*/  ehb () ; 
 int /*<<< orphan*/  read_c0_status () ; 
 int /*<<< orphan*/  write_c0_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_mips_set_c0_status(void)
{
	u32 status = read_c0_status();

	if (cpu_has_dsp)
		status |= (ST0_MX);

	write_c0_status(status);
	ehb();
}