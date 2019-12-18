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
struct ntb_dev {int /*<<< orphan*/  pdev; } ;
struct idt_ntb_dev {int mw_cnt; TYPE_1__* mws; } ;
typedef  int resource_size_t ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {int idx; int size_max; int /*<<< orphan*/  bar; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static int idt_ntb_peer_mw_get_addr(struct ntb_dev *ntb, int widx,
				    phys_addr_t *base, resource_size_t *size)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (widx < 0 || ndev->mw_cnt <= widx)
		return -EINVAL;

	/* Mapping address is just properly shifted BAR resource start */
	if (base != NULL)
		*base = pci_resource_start(ntb->pdev, ndev->mws[widx].bar) +
			ndev->mws[widx].idx * ndev->mws[widx].size_max;

	/* Mapping size has already been calculated at MWs scanning */
	if (size != NULL)
		*size = ndev->mws[widx].size_max;

	return 0;
}