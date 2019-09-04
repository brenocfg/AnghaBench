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

/* Variables and functions */
 int /*<<< orphan*/  gpmc_cs_delete_mem (int) ; 
 int /*<<< orphan*/  gpmc_cs_mem_enabled (int) ; 
 int gpmc_cs_num ; 

__attribute__((used)) static void gpmc_mem_exit(void)
{
	int cs;

	for (cs = 0; cs < gpmc_cs_num; cs++) {
		if (!gpmc_cs_mem_enabled(cs))
			continue;
		gpmc_cs_delete_mem(cs);
	}

}