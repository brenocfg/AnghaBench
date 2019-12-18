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
typedef  scalar_t__ u32 ;
struct xhci_input_control_ctx {int dummy; } ;
struct xhci_hcd {int /*<<< orphan*/  num_active_eps; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_xhci_dbg_quirks ; 
 scalar_t__ xhci_count_num_dropped_endpoints (struct xhci_hcd*,struct xhci_input_control_ctx*) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_finish_resource_reservation(struct xhci_hcd *xhci,
		struct xhci_input_control_ctx *ctrl_ctx)
{
	u32 num_dropped_eps;

	num_dropped_eps = xhci_count_num_dropped_endpoints(xhci, ctrl_ctx);
	xhci->num_active_eps -= num_dropped_eps;
	if (num_dropped_eps)
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Removing %u dropped ep ctxs, %u now active.",
				num_dropped_eps,
				xhci->num_active_eps);
}