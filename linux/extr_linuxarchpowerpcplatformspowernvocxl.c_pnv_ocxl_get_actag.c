#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  dev; } ;
struct npu_link {int /*<<< orphan*/ * fn_desired_actags; TYPE_1__* fn_actags; int /*<<< orphan*/  assignment_done; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_actags (struct npu_link*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct npu_link* find_link (struct pci_dev*) ; 
 int /*<<< orphan*/  links_list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int pnv_ocxl_get_actag(struct pci_dev *dev, u16 *base, u16 *enabled,
		u16 *supported)
{
	struct npu_link *link;

	mutex_lock(&links_list_lock);

	link = find_link(dev);
	if (!link) {
		dev_err(&dev->dev, "actag information not found\n");
		mutex_unlock(&links_list_lock);
		return -ENODEV;
	}
	/*
	 * On p9, we only have 64 actags per link, so they must be
	 * shared by all the functions of the same adapter. We counted
	 * the desired actag counts during PCI enumeration, so that we
	 * can allocate a pro-rated number of actags to each function.
	 */
	if (!link->assignment_done)
		assign_actags(link);

	*base      = link->fn_actags[PCI_FUNC(dev->devfn)].start;
	*enabled   = link->fn_actags[PCI_FUNC(dev->devfn)].count;
	*supported = link->fn_desired_actags[PCI_FUNC(dev->devfn)];

	mutex_unlock(&links_list_lock);
	return 0;
}