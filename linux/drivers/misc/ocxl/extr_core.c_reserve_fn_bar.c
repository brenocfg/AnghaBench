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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ocxl_fn {int /*<<< orphan*/ * bar_used; TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int pci_request_region (struct pci_dev*,int,char*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reserve_fn_bar(struct ocxl_fn *fn, int bar)
{
	struct pci_dev *dev = to_pci_dev(fn->dev.parent);
	int rc, idx;

	if (bar != 0 && bar != 2 && bar != 4)
		return -EINVAL;

	idx = bar >> 1;
	if (fn->bar_used[idx]++ == 0) {
		rc = pci_request_region(dev, bar, "ocxl");
		if (rc)
			return rc;
	}
	return 0;
}