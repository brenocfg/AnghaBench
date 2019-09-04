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
typedef  scalar_t__ u32 ;
struct armada_37xx_dvfs {scalar_t__ cpu_freq_max; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct armada_37xx_dvfs*) ; 
 struct armada_37xx_dvfs* armada_37xx_dvfs ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static struct armada_37xx_dvfs *armada_37xx_cpu_freq_info_get(u32 freq)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(armada_37xx_dvfs); i++) {
		if (freq == armada_37xx_dvfs[i].cpu_freq_max)
			return &armada_37xx_dvfs[i];
	}

	pr_err("Unsupported CPU frequency %d MHz\n", freq/1000000);
	return NULL;
}