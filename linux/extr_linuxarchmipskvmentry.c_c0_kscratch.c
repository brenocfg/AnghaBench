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
#define  CPU_XLP 129 
#define  CPU_XLR 128 
 int boot_cpu_type () ; 

__attribute__((used)) static int c0_kscratch(void)
{
	switch (boot_cpu_type()) {
	case CPU_XLP:
	case CPU_XLR:
		return 22;
	default:
		return 31;
	}
}