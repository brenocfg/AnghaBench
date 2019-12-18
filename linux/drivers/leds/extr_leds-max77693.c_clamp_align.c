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
 int clamp_val (int,int,int) ; 

__attribute__((used)) static void clamp_align(u32 *v, u32 min, u32 max, u32 step)
{
	*v = clamp_val(*v, min, max);
	if (step > 1)
		*v = (*v - min) / step * step + min;
}