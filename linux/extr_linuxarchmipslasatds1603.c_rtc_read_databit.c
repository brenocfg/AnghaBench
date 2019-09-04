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
struct TYPE_2__ {int data_read_shift; } ;

/* Variables and functions */
 TYPE_1__* ds1603 ; 
 int /*<<< orphan*/  rtc_cycle_clock (int /*<<< orphan*/ ) ; 
 int rtc_datareg_read () ; 
 int /*<<< orphan*/  rtc_reg_read () ; 

__attribute__((used)) static unsigned int rtc_read_databit(void)
{
	unsigned int data;

	data = (rtc_datareg_read() & (1 << ds1603->data_read_shift))
		>> ds1603->data_read_shift;
	rtc_cycle_clock(rtc_reg_read());
	return data;
}