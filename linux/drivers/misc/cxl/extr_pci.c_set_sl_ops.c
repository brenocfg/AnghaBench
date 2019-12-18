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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cxl {TYPE_1__* native; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sl_ops; } ;

/* Variables and functions */
 scalar_t__ cxl_is_power8 () ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  psl8_ops ; 
 int /*<<< orphan*/  psl9_ops ; 

__attribute__((used)) static void set_sl_ops(struct cxl *adapter, struct pci_dev *dev)
{
	if (cxl_is_power8()) {
		dev_info(&dev->dev, "Device uses a PSL8\n");
		adapter->native->sl_ops = &psl8_ops;
	} else {
		dev_info(&dev->dev, "Device uses a PSL9\n");
		adapter->native->sl_ops = &psl9_ops;
	}
}