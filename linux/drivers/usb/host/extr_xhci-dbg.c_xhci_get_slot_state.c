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
struct xhci_slot_ctx {int /*<<< orphan*/  dev_state; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_container_ctx {int dummy; } ;

/* Variables and functions */
 int GET_SLOT_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct xhci_slot_ctx* xhci_get_slot_ctx (struct xhci_hcd*,struct xhci_container_ctx*) ; 
 char* xhci_slot_state_string (int) ; 

char *xhci_get_slot_state(struct xhci_hcd *xhci,
		struct xhci_container_ctx *ctx)
{
	struct xhci_slot_ctx *slot_ctx = xhci_get_slot_ctx(xhci, ctx);
	int state = GET_SLOT_STATE(le32_to_cpu(slot_ctx->dev_state));

	return xhci_slot_state_string(state);
}