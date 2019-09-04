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
struct TYPE_2__ {unsigned long clk; unsigned long data; int huge_delay; scalar_t__ data_reversed; } ;

/* Variables and functions */
 TYPE_1__* ds1603 ; 
 int /*<<< orphan*/  lasat_ndelay (int) ; 
 int /*<<< orphan*/  rtc_reg_write (unsigned long) ; 

__attribute__((used)) static void rtc_cycle_clock(unsigned long data)
{
	data |= ds1603->clk;
	rtc_reg_write(data);
	lasat_ndelay(250);
	if (ds1603->data_reversed)
		data &= ~ds1603->data;
	else
		data |= ds1603->data;
	data &= ~ds1603->clk;
	rtc_reg_write(data);
	lasat_ndelay(250 + ds1603->huge_delay);
}