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
struct atmel_ehci_priv {int clocked; int /*<<< orphan*/  iclk; int /*<<< orphan*/  uclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_start_clock(struct atmel_ehci_priv *atmel_ehci)
{
	if (atmel_ehci->clocked)
		return;

	clk_prepare_enable(atmel_ehci->uclk);
	clk_prepare_enable(atmel_ehci->iclk);
	atmel_ehci->clocked = true;
}