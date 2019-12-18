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
struct xhci_hcd {int dummy; } ;
struct xhci_command {int slot_id; } ;

/* Variables and functions */
 scalar_t__ COMP_SUCCESS ; 

__attribute__((used)) static void xhci_handle_cmd_enable_slot(struct xhci_hcd *xhci, int slot_id,
		struct xhci_command *command, u32 cmd_comp_code)
{
	if (cmd_comp_code == COMP_SUCCESS)
		command->slot_id = slot_id;
	else
		command->slot_id = 0;
}