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
struct cpuidle_driver {int dummy; } ;

/* Variables and functions */
 struct cpuidle_driver* cpuidle_curr_driver ; 

__attribute__((used)) static inline struct cpuidle_driver *__cpuidle_get_cpu_driver(int cpu)
{
	return cpuidle_curr_driver;
}