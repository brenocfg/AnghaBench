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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bL_cpufreq_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ve_spc_cpufreq_ops ; 

__attribute__((used)) static int ve_spc_cpufreq_remove(struct platform_device *pdev)
{
	bL_cpufreq_unregister(&ve_spc_cpufreq_ops);
	return 0;
}