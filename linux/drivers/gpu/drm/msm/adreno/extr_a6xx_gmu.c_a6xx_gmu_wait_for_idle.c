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
struct a6xx_gmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  a6xx_gmu_check_idle_level (struct a6xx_gmu*) ; 
 int spin_until (int /*<<< orphan*/ ) ; 

int a6xx_gmu_wait_for_idle(struct a6xx_gmu *gmu)
{
	return spin_until(a6xx_gmu_check_idle_level(gmu));
}