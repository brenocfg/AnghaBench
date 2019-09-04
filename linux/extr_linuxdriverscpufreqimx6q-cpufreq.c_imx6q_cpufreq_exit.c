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
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev ; 
 int /*<<< orphan*/  cpufreq_cooling_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx6q_cpufreq_exit(struct cpufreq_policy *policy)
{
	cpufreq_cooling_unregister(cdev);

	return 0;
}