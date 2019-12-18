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
struct pp_hwmgr {int dummy; } ;
struct amd_pp_simple_clock_info {int engine_max_clock; } ;

/* Variables and functions */

__attribute__((used)) static int smu10_get_max_high_clocks(struct pp_hwmgr *hwmgr, struct amd_pp_simple_clock_info *clocks)
{
	clocks->engine_max_clock = 80000; /* driver can't get engine clock, temp hard code to 800MHz */
	return 0;
}