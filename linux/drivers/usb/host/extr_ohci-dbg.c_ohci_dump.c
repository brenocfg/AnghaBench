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
struct ohci_hcd {scalar_t__ hcca; } ;

/* Variables and functions */
 int /*<<< orphan*/  ohci_dbg (struct ohci_hcd*,char*,...) ; 
 int /*<<< orphan*/  ohci_dump_roothub (struct ohci_hcd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_dump_status (struct ohci_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_frame_no (struct ohci_hcd*) ; 

__attribute__((used)) static void ohci_dump(struct ohci_hcd *controller)
{
	ohci_dbg (controller, "OHCI controller state\n");

	// dumps some of the state we know about
	ohci_dump_status (controller, NULL, NULL);
	if (controller->hcca)
		ohci_dbg (controller,
			"hcca frame #%04x\n", ohci_frame_no(controller));
	ohci_dump_roothub (controller, 1, NULL, NULL);
}