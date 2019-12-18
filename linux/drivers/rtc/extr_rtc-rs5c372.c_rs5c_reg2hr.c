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
struct rs5c372 {scalar_t__ time24; } ;

/* Variables and functions */
 int bcd2bin (unsigned int) ; 

__attribute__((used)) static unsigned rs5c_reg2hr(struct rs5c372 *rs5c, unsigned reg)
{
	unsigned	hour;

	if (rs5c->time24)
		return bcd2bin(reg & 0x3f);

	hour = bcd2bin(reg & 0x1f);
	if (hour == 12)
		hour = 0;
	if (reg & 0x20)
		hour += 12;
	return hour;
}