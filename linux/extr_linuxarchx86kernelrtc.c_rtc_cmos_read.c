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
 int /*<<< orphan*/  RTC_PORT (int) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_cmos_prefix (unsigned char) ; 
 int /*<<< orphan*/  lock_cmos_suffix (unsigned char) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

unsigned char rtc_cmos_read(unsigned char addr)
{
	unsigned char val;

	lock_cmos_prefix(addr);
	outb(addr, RTC_PORT(0));
	val = inb(RTC_PORT(1));
	lock_cmos_suffix(addr);

	return val;
}