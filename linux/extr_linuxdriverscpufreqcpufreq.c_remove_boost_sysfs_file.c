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
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 TYPE_1__ boost ; 
 scalar_t__ cpufreq_boost_supported () ; 
 int /*<<< orphan*/  cpufreq_global_kobject ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_boost_sysfs_file(void)
{
	if (cpufreq_boost_supported())
		sysfs_remove_file(cpufreq_global_kobject, &boost.attr);
}