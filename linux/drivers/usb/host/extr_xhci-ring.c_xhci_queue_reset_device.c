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
typedef  int /*<<< orphan*/  u32 ;
struct xhci_hcd {int dummy; } ;
struct xhci_command {int dummy; } ;

/* Variables and functions */
 int SLOT_ID_FOR_TRB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRB_RESET_DEV ; 
 int TRB_TYPE (int /*<<< orphan*/ ) ; 
 int queue_command (struct xhci_hcd*,struct xhci_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int xhci_queue_reset_device(struct xhci_hcd *xhci, struct xhci_command *cmd,
		u32 slot_id)
{
	return queue_command(xhci, cmd, 0, 0, 0,
			TRB_TYPE(TRB_RESET_DEV) | SLOT_ID_FOR_TRB(slot_id),
			false);
}