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
struct pxa_cpufreq_data {int /*<<< orphan*/  clk_core; } ;

/* Variables and functions */
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 struct pxa_cpufreq_data* cpufreq_get_driver_data () ; 

__attribute__((used)) static unsigned int pxa_cpufreq_get(unsigned int cpu)
{
	struct pxa_cpufreq_data *data = cpufreq_get_driver_data();

	return (unsigned int) clk_get_rate(data->clk_core) / 1000;
}