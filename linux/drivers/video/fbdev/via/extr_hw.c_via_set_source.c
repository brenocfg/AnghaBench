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
 int VIA_LDVP0 ; 
 int VIA_LDVP1 ; 
 int VIA_LVDS1 ; 
 int VIA_LVDS2 ; 
 int /*<<< orphan*/  set_crt_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dvp0_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dvp1_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ldvp0_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ldvp1_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_lvds1_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_lvds2_source (int /*<<< orphan*/ ) ; 

void via_set_source(u32 devices, u8 iga)
{
	if (devices & VIA_LDVP0)
		set_ldvp0_source(iga);
	if (devices & VIA_LDVP1)
		set_ldvp1_source(iga);
	if (devices & VIA_DVP0)
		set_dvp0_source(iga);
	if (devices & VIA_CRT)
		set_crt_source(iga);
	if (devices & VIA_DVP1)
		set_dvp1_source(iga);
	if (devices & VIA_LVDS1)
		set_lvds1_source(iga);
	if (devices & VIA_LVDS2)
		set_lvds2_source(iga);
}