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
typedef  int /*<<< orphan*/  u16 ;
struct hfi1_devdata {int lbus_width; int lbus_speed; int /*<<< orphan*/  lbus_info; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int extract_speed (int /*<<< orphan*/ ) ; 
 int extract_width (int /*<<< orphan*/ ) ; 
 int pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static void update_lbus_info(struct hfi1_devdata *dd)
{
	u16 linkstat;
	int ret;

	ret = pcie_capability_read_word(dd->pcidev, PCI_EXP_LNKSTA, &linkstat);
	if (ret) {
		dd_dev_err(dd, "Unable to read from PCI config\n");
		return;
	}

	dd->lbus_width = extract_width(linkstat);
	dd->lbus_speed = extract_speed(linkstat);
	snprintf(dd->lbus_info, sizeof(dd->lbus_info),
		 "PCIe,%uMHz,x%u", dd->lbus_speed, dd->lbus_width);
}