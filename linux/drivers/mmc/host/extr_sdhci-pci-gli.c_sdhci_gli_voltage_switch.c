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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void sdhci_gli_voltage_switch(struct sdhci_host *host)
{
	/*
	 * According to Section 3.6.1 signal voltage switch procedure in
	 * SD Host Controller Simplified Spec. 4.20, steps 6~8 are as
	 * follows:
	 * (6) Set 1.8V Signal Enable in the Host Control 2 register.
	 * (7) Wait 5ms. 1.8V voltage regulator shall be stable within this
	 *     period.
	 * (8) If 1.8V Signal Enable is cleared by Host Controller, go to
	 *     step (12).
	 *
	 * Wait 5ms after set 1.8V signal enable in Host Control 2 register
	 * to ensure 1.8V signal enable bit is set by GL9750/GL9755.
	 */
	usleep_range(5000, 5500);
}