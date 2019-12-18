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
 scalar_t__ IOP_WDTCR_DIS_ARM ; 
 scalar_t__ IOP_WDTCR_EN_ARM ; 

__attribute__((used)) static int wdt_supports_disable(void)
{
	int can_disable;

	if (IOP_WDTCR_EN_ARM != IOP_WDTCR_DIS_ARM)
		can_disable = 1;
	else
		can_disable = 0;

	return can_disable;
}