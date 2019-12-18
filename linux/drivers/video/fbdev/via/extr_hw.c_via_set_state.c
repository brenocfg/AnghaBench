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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int VIA_CRT ; 
 int VIA_DVP0 ; 
 int VIA_DVP1 ; 
 int VIA_LVDS1 ; 
 int VIA_LVDS2 ; 
 int /*<<< orphan*/  set_crt_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dvp0_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dvp1_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_lvds1_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_lvds2_state (int /*<<< orphan*/ ) ; 

void via_set_state(u32 devices, u8 state)
{
	/*
	TODO: Can we enable/disable these devices? How?
	if (devices & VIA_LDVP0)
	if (devices & VIA_LDVP1)
	*/
	if (devices & VIA_DVP0)
		set_dvp0_state(state);
	if (devices & VIA_CRT)
		set_crt_state(state);
	if (devices & VIA_DVP1)
		set_dvp1_state(state);
	if (devices & VIA_LVDS1)
		set_lvds1_state(state);
	if (devices & VIA_LVDS2)
		set_lvds2_state(state);
}