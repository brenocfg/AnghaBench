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
struct TYPE_2__ {scalar_t__ x86_vendor; int x86; } ;

/* Variables and functions */
 scalar_t__ X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static bool is_blacklisted_cpu(void)
{
	if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL)
		return false;

	if (boot_cpu_data.x86 == 0x0f) {
		/*
		 * On Pentium 4, blowfish-x86_64 is slower than generic C
		 * implementation because use of 64bit rotates (which are really
		 * slow on P4). Therefore blacklist P4s.
		 */
		return true;
	}

	return false;
}