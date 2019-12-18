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
struct xhci_regset {int /*<<< orphan*/  list; } ;
struct xhci_hcd {int /*<<< orphan*/  regset_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct xhci_regset* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct xhci_regset *xhci_debugfs_alloc_regset(struct xhci_hcd *xhci)
{
	struct xhci_regset	*regset;

	regset = kzalloc(sizeof(*regset), GFP_KERNEL);
	if (!regset)
		return NULL;

	/*
	 * The allocation and free of regset are executed in order.
	 * We needn't a lock here.
	 */
	INIT_LIST_HEAD(&regset->list);
	list_add_tail(&regset->list, &xhci->regset_list);

	return regset;
}