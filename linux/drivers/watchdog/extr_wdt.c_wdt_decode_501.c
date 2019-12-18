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
 int WDC_SR_PSUOVER ; 
 int WDC_SR_PSUUNDR ; 
 int WDC_SR_TGOOD ; 
 int /*<<< orphan*/  WDT_RT ; 
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*,...) ; 

__attribute__((used)) static void wdt_decode_501(int status)
{
	if (!(status & WDC_SR_TGOOD))
		pr_crit("Overheat alarm (%d)\n", inb_p(WDT_RT));
	if (!(status & WDC_SR_PSUOVER))
		pr_crit("PSU over voltage\n");
	if (!(status & WDC_SR_PSUUNDR))
		pr_crit("PSU under voltage\n");
}