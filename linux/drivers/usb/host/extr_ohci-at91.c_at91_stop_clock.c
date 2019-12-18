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
struct ohci_at91_priv {int clocked; int /*<<< orphan*/  hclk; int /*<<< orphan*/  iclk; int /*<<< orphan*/  fclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at91_stop_clock(struct ohci_at91_priv *ohci_at91)
{
	if (!ohci_at91->clocked)
		return;

	clk_disable_unprepare(ohci_at91->fclk);
	clk_disable_unprepare(ohci_at91->iclk);
	clk_disable_unprepare(ohci_at91->hclk);
	ohci_at91->clocked = false;
}