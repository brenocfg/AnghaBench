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
struct xhci_hcd {int /*<<< orphan*/  cmd_timer; } ;

/* Variables and functions */
 int mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static bool xhci_mod_cmd_timer(struct xhci_hcd *xhci, unsigned long delay)
{
	return mod_delayed_work(system_wq, &xhci->cmd_timer, delay);
}