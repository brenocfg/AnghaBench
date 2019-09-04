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
struct cxl_afu {int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_adapter_vpd ) (int /*<<< orphan*/ ,void*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ IS_ERR (struct cxl_afu*) ; 
 TYPE_1__* cxl_ops ; 
 struct cxl_afu* cxl_pci_to_afu (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,size_t) ; 

ssize_t cxl_read_adapter_vpd(struct pci_dev *dev, void *buf, size_t count)
{
	struct cxl_afu *afu = cxl_pci_to_afu(dev);
	if (IS_ERR(afu))
		return -ENODEV;

	return cxl_ops->read_adapter_vpd(afu->adapter, buf, count);
}