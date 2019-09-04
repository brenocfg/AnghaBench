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
typedef  int u64 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  cppc_find_dmi_mhz ; 
 int /*<<< orphan*/  dmi_walk (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u64 cppc_get_dmi_max_khz(void)
{
	u16 mhz = 0;

	dmi_walk(cppc_find_dmi_mhz, &mhz);

	/*
	 * Real stupid fallback value, just in case there is no
	 * actual value set.
	 */
	mhz = mhz ? mhz : 1;

	return (1000 * mhz);
}