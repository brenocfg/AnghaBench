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

void gsc_get_prescaler_shfactor(u32 hratio, u32 vratio, u32 *sh)
{
	if (hratio == 4 && vratio == 4)
		*sh = 4;
	else if ((hratio == 4 && vratio == 2) ||
		 (hratio == 2 && vratio == 4))
		*sh = 3;
	else if ((hratio == 4 && vratio == 1) ||
		 (hratio == 1 && vratio == 4) ||
		 (hratio == 2 && vratio == 2))
		*sh = 2;
	else if (hratio == 1 && vratio == 1)
		*sh = 0;
	else
		*sh = 1;
}