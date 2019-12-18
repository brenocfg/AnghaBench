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
struct mmci_host {int cclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mmci_reg_delay(struct mmci_host *host)
{
	/*
	 * According to the spec, at least three feedback clock cycles
	 * of max 52 MHz must pass between two writes to the MMCICLOCK reg.
	 * Three MCLK clock cycles must pass between two MMCIPOWER reg writes.
	 * Worst delay time during card init is at 100 kHz => 30 us.
	 * Worst delay time when up and running is at 25 MHz => 120 ns.
	 */
	if (host->cclk < 25000000)
		udelay(30);
	else
		ndelay(120);
}