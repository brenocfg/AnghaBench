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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int mc146818_set_time (struct rtc_time*) ; 

__attribute__((used)) static int cmos_set_time(struct device *dev, struct rtc_time *t)
{
	/* REVISIT:  set the "century" register if available
	 *
	 * NOTE: this ignores the issue whereby updating the seconds
	 * takes effect exactly 500ms after we write the register.
	 * (Also queueing and other delays before we get this far.)
	 */
	return mc146818_set_time(t);
}