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
struct ntb_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct intel_ntb_dev {int b2b_idx; int /*<<< orphan*/  b2b_off; TYPE_1__ ntb; } ;
typedef  scalar_t__ resource_size_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ndev_mw_to_bar (struct intel_ntb_dev*,int) ; 
 struct intel_ntb_dev* ntb_ndev (struct ntb_dev*) ; 
 scalar_t__ pci_resource_len (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int) ; 

int intel_ntb_peer_mw_get_addr(struct ntb_dev *ntb, int idx,
			       phys_addr_t *base, resource_size_t *size)
{
	struct intel_ntb_dev *ndev = ntb_ndev(ntb);
	int bar;

	if (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	bar = ndev_mw_to_bar(ndev, idx);
	if (bar < 0)
		return bar;

	if (base)
		*base = pci_resource_start(ndev->ntb.pdev, bar) +
			(idx == ndev->b2b_idx ? ndev->b2b_off : 0);

	if (size)
		*size = pci_resource_len(ndev->ntb.pdev, bar) -
			(idx == ndev->b2b_idx ? ndev->b2b_off : 0);

	return 0;
}