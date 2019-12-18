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

__attribute__((used)) static u32 MT2063_Round_fLO(u32 f_LO, u32 f_LO_Step, u32 f_ref)
{
	return f_ref * (f_LO / f_ref)
	    + f_LO_Step * (((f_LO % f_ref) + (f_LO_Step / 2)) / f_LO_Step);
}