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
struct sh_rtc {scalar_t__ regbase; } ;

/* Variables and functions */
 unsigned int AR_ENB ; 
 int bcd2bin (unsigned int) ; 
 unsigned int readb (scalar_t__) ; 

__attribute__((used)) static inline int sh_rtc_read_alarm_value(struct sh_rtc *rtc, int reg_off)
{
	unsigned int byte;
	int value = -1;			/* return -1 for ignored values */

	byte = readb(rtc->regbase + reg_off);
	if (byte & AR_ENB) {
		byte &= ~AR_ENB;	/* strip the enable bit */
		value = bcd2bin(byte);
	}

	return value;
}