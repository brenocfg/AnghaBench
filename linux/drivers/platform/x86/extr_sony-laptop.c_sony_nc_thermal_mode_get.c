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
 int EIO ; 
 scalar_t__ sony_call_snc_handle (int,int,unsigned int*) ; 

__attribute__((used)) static int sony_nc_thermal_mode_get(void)
{
	unsigned int result;

	if (sony_call_snc_handle(0x0122, 0x0100, &result))
		return -EIO;

	return result & 0xff;
}