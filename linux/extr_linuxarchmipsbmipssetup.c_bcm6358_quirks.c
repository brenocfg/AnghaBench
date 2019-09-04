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
 scalar_t__ bmips_smp_enabled ; 

__attribute__((used)) static void bcm6358_quirks(void)
{
	/*
	 * BCM3368/BCM6358 need special handling for their shared TLB, so
	 * disable SMP for now
	 */
	bmips_smp_enabled = 0;
}