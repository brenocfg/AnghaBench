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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct cxl {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_vpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

ssize_t cxl_pci_read_adapter_vpd(struct cxl *adapter, void *buf, size_t len)
{
	return pci_read_vpd(to_pci_dev(adapter->dev.parent), 0, len, buf);
}