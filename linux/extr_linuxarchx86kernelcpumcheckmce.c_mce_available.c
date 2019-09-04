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
 int /*<<< orphan*/  X86_FEATURE_MCA ; 
 int /*<<< orphan*/  X86_FEATURE_MCE ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 TYPE_1__ mca_cfg ; 

int mce_available(struct cpuinfo_x86 *c)
{
	if (mca_cfg.disabled)
		return 0;
	return cpu_has(c, X86_FEATURE_MCE) && cpu_has(c, X86_FEATURE_MCA);
}