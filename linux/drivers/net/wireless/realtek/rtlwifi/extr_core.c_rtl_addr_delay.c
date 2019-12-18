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
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void rtl_addr_delay(u32 addr)
{
	if (addr == 0xfe)
		mdelay(50);
	else if (addr == 0xfd)
		msleep(5);
	else if (addr == 0xfc)
		msleep(1);
	else if (addr == 0xfb)
		usleep_range(50, 100);
	else if (addr == 0xfa)
		usleep_range(5, 10);
	else if (addr == 0xf9)
		usleep_range(1, 2);
}