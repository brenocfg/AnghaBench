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
 scalar_t__ MPC512x_SOC_MPC5125 ; 
 scalar_t__ soc ; 

__attribute__((used)) static int soc_max_pscnum(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		return 10;
	return 12;
}