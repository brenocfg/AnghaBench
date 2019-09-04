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

bool dpp1_dscl_is_lb_conf_valid(int ceil_vratio, int num_partitions, int vtaps)
{
	if (ceil_vratio > 2)
		return vtaps <= (num_partitions - ceil_vratio + 2);
	else
		return vtaps <= num_partitions;
}