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
struct fhci_hcd {int /*<<< orphan*/  empty_eds; } ;
struct ed {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_ed (struct ed*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void fhci_recycle_empty_ed(struct fhci_hcd *fhci, struct ed *ed)
{
	init_ed(ed);
	list_add(&ed->node, &fhci->empty_eds);
}