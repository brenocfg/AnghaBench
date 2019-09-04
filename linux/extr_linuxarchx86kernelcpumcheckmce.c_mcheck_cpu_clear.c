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
struct cpuinfo_x86 {int dummy; } ;
struct TYPE_2__ {scalar_t__ disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mcheck_cpu_clear_vendor (struct cpuinfo_x86*) ; 
 TYPE_1__ mca_cfg ; 
 int /*<<< orphan*/  mce_available (struct cpuinfo_x86*) ; 

void mcheck_cpu_clear(struct cpuinfo_x86 *c)
{
	if (mca_cfg.disabled)
		return;

	if (!mce_available(c))
		return;

	/*
	 * Possibly to clear general settings generic to x86
	 * __mcheck_cpu_clear_generic(c);
	 */
	__mcheck_cpu_clear_vendor(c);

}