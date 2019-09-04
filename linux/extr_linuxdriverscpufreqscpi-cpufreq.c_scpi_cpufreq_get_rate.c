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
struct scpi_data {int /*<<< orphan*/  clk; } ;
struct cpufreq_policy {struct scpi_data* driver_data; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct cpufreq_policy* cpufreq_cpu_get_raw (unsigned int) ; 

__attribute__((used)) static unsigned int scpi_cpufreq_get_rate(unsigned int cpu)
{
	struct cpufreq_policy *policy = cpufreq_cpu_get_raw(cpu);
	struct scpi_data *priv = policy->driver_data;
	unsigned long rate = clk_get_rate(priv->clk);

	return rate / 1000;
}