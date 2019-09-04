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
struct TYPE_2__ {int rst; } ;

/* Variables and functions */
 TYPE_1__* ds1603 ; 
 int rtc_reg_read () ; 
 int /*<<< orphan*/  rtc_reg_write (int) ; 

__attribute__((used)) static void rtc_nrst_high(void)
{
	rtc_reg_write(rtc_reg_read() | ds1603->rst);
}