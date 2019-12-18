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
struct xhci_hcd_histb {int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  utmi_clk; int /*<<< orphan*/  pipe_clk; int /*<<< orphan*/  suspend_clk; int /*<<< orphan*/  soft_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_histb_host_disable(struct xhci_hcd_histb *histb)
{
	reset_control_assert(histb->soft_reset);

	clk_disable_unprepare(histb->suspend_clk);
	clk_disable_unprepare(histb->pipe_clk);
	clk_disable_unprepare(histb->utmi_clk);
	clk_disable_unprepare(histb->bus_clk);
}