#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; } ;
struct cx88_core {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* cx88_boards ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void cx88_card_list(struct cx88_core *core, struct pci_dev *pci)
{
	int i;

	if (!pci->subsystem_vendor && !pci->subsystem_device) {
		pr_err("Your board has no valid PCI Subsystem ID and thus can't\n");
		pr_err("be autodetected.  Please pass card=<n> insmod option to\n");
		pr_err("workaround that.  Redirect complaints to the vendor of\n");
		pr_err("the TV card\n");
	} else {
		pr_err("Your board isn't known (yet) to the driver.  You can\n");
		pr_err("try to pick one of the existing card configs via\n");
		pr_err("card=<n> insmod option.  Updating to the latest\n");
		pr_err("version might help as well.\n");
	}
	pr_err("Here is a list of valid choices for the card=<n> insmod option:\n");
	for (i = 0; i < ARRAY_SIZE(cx88_boards); i++)
		pr_err("    card=%d -> %s\n", i, cx88_boards[i].name);
}