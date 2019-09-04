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
struct cpuinfo_mips {int dummy; } ;

/* Variables and functions */
#define  LEGACY 131 
#define  RELAXED 130 
#define  STD2008 129 
#define  STRICT 128 
 int /*<<< orphan*/  cpu_has_nan_2008 ; 
 int /*<<< orphan*/  cpu_has_nan_legacy ; 
 int ieee754 ; 
 int mips_use_nan_2008 ; 
 int mips_use_nan_legacy ; 

__attribute__((used)) static void cpu_set_nan_2008(struct cpuinfo_mips *c)
{
	switch (ieee754) {
	case STRICT:
		mips_use_nan_legacy = !!cpu_has_nan_legacy;
		mips_use_nan_2008 = !!cpu_has_nan_2008;
		break;
	case LEGACY:
		mips_use_nan_legacy = !!cpu_has_nan_legacy;
		mips_use_nan_2008 = !cpu_has_nan_legacy;
		break;
	case STD2008:
		mips_use_nan_legacy = !cpu_has_nan_2008;
		mips_use_nan_2008 = !!cpu_has_nan_2008;
		break;
	case RELAXED:
		mips_use_nan_legacy = true;
		mips_use_nan_2008 = true;
		break;
	}
}