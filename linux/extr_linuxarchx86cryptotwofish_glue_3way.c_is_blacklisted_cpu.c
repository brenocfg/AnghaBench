#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ x86_vendor; int x86; int x86_model; } ;

/* Variables and functions */
 scalar_t__ X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static bool is_blacklisted_cpu(void)
{
	if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL)
		return false;

	if (boot_cpu_data.x86 == 0x06 &&
		(boot_cpu_data.x86_model == 0x1c ||
		 boot_cpu_data.x86_model == 0x26 ||
		 boot_cpu_data.x86_model == 0x36)) {
		/*
		 * On Atom, twofish-3way is slower than original assembler
		 * implementation. Twofish-3way trades off some performance in
		 * storing blocks in 64bit registers to allow three blocks to
		 * be processed parallel. Parallel operation then allows gaining
		 * more performance than was trade off, on out-of-order CPUs.
		 * However Atom does not benefit from this parallellism and
		 * should be blacklisted.
		 */
		return true;
	}

	if (boot_cpu_data.x86 == 0x0f) {
		/*
		 * On Pentium 4, twofish-3way is slower than original assembler
		 * implementation because excessive uses of 64bit rotate and
		 * left-shifts (which are really slow on P4) needed to store and
		 * handle 128bit block in two 64bit registers.
		 */
		return true;
	}

	return false;
}