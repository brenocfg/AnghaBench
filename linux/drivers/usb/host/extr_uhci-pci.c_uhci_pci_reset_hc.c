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
struct uhci_hcd {int /*<<< orphan*/  io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_dev (struct uhci_hcd*) ; 
 int /*<<< orphan*/  uhci_reset_hc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uhci_pci_reset_hc(struct uhci_hcd *uhci)
{
	uhci_reset_hc(to_pci_dev(uhci_dev(uhci)), uhci->io_addr);
}