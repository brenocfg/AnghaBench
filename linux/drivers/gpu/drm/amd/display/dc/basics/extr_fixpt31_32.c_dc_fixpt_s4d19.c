#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fixed31_32 {scalar_t__ value; } ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 TYPE_1__ dc_fixpt_abs (struct fixed31_32) ; 
 int ux_dy (scalar_t__,int,int) ; 

int dc_fixpt_s4d19(struct fixed31_32 arg)
{
	if (arg.value < 0)
		return -(int)ux_dy(dc_fixpt_abs(arg).value, 4, 19);
	else
		return ux_dy(arg.value, 4, 19);
}