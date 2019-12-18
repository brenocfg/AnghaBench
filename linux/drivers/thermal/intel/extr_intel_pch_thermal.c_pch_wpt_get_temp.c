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
typedef  int u16 ;
struct pch_thermal_device {scalar_t__ hw_base; } ;

/* Variables and functions */
 scalar_t__ WPT_TEMP ; 
 int WPT_TEMP_TSR ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static int pch_wpt_get_temp(struct pch_thermal_device *ptd, int *temp)
{
	u16 wpt_temp;

	wpt_temp = WPT_TEMP_TSR & readw(ptd->hw_base + WPT_TEMP);

	/* Resolution of 1/2 degree C and an offset of -50C */
	*temp = (wpt_temp * 1000 / 2 - 50000);

	return 0;
}