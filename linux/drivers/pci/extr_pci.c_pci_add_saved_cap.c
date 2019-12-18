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
struct pci_dev {int /*<<< orphan*/  saved_cap_space; } ;
struct pci_cap_saved_state {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_add_saved_cap(struct pci_dev *pci_dev,
	struct pci_cap_saved_state *new_cap)
{
	hlist_add_head(&new_cap->next, &pci_dev->saved_cap_space);
}