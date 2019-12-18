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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 ath9k_rng_delay_get(u32 fail_stats)
{
	u32 delay;

	if (fail_stats < 100)
		delay = 10;
	else if (fail_stats < 105)
		delay = 1000;
	else
		delay = 10000;

	return delay;
}