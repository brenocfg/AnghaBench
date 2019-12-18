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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ U300_WDOG_CR ; 
 int U300_WDOG_CR_COUNT_VALUE_MASK ; 
 int U300_WDOG_CR_VALID_IND ; 
 int readw (scalar_t__) ; 
 scalar_t__ virtbase ; 

__attribute__((used)) static unsigned int coh901327_gettimeleft(struct watchdog_device *wdt_dev)
{
	u16 val;

	/* Read repeatedly until the value is stable! */
	val = readw(virtbase + U300_WDOG_CR);
	while (val & U300_WDOG_CR_VALID_IND)
		val = readw(virtbase + U300_WDOG_CR);
	val &= U300_WDOG_CR_COUNT_VALUE_MASK;
	if (val != 0)
		val /= 100;

	return val;
}