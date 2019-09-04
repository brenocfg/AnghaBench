#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct amd64_pvt {TYPE_1__* F3; TYPE_1__* F2; TYPE_1__* F1; TYPE_1__* F6; TYPE_1__* F0; scalar_t__ umc; } ;
struct TYPE_4__ {int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  amd64_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_1__*) ; 
 void* pci_get_related_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pci_name (TYPE_1__*) ; 

__attribute__((used)) static int
reserve_mc_sibling_devs(struct amd64_pvt *pvt, u16 pci_id1, u16 pci_id2)
{
	if (pvt->umc) {
		pvt->F0 = pci_get_related_function(pvt->F3->vendor, pci_id1, pvt->F3);
		if (!pvt->F0) {
			amd64_err("F0 not found, device 0x%x (broken BIOS?)\n", pci_id1);
			return -ENODEV;
		}

		pvt->F6 = pci_get_related_function(pvt->F3->vendor, pci_id2, pvt->F3);
		if (!pvt->F6) {
			pci_dev_put(pvt->F0);
			pvt->F0 = NULL;

			amd64_err("F6 not found: device 0x%x (broken BIOS?)\n", pci_id2);
			return -ENODEV;
		}

		edac_dbg(1, "F0: %s\n", pci_name(pvt->F0));
		edac_dbg(1, "F3: %s\n", pci_name(pvt->F3));
		edac_dbg(1, "F6: %s\n", pci_name(pvt->F6));

		return 0;
	}

	/* Reserve the ADDRESS MAP Device */
	pvt->F1 = pci_get_related_function(pvt->F3->vendor, pci_id1, pvt->F3);
	if (!pvt->F1) {
		amd64_err("F1 not found: device 0x%x (broken BIOS?)\n", pci_id1);
		return -ENODEV;
	}

	/* Reserve the DCT Device */
	pvt->F2 = pci_get_related_function(pvt->F3->vendor, pci_id2, pvt->F3);
	if (!pvt->F2) {
		pci_dev_put(pvt->F1);
		pvt->F1 = NULL;

		amd64_err("F2 not found: device 0x%x (broken BIOS?)\n", pci_id2);
		return -ENODEV;
	}

	edac_dbg(1, "F1: %s\n", pci_name(pvt->F1));
	edac_dbg(1, "F2: %s\n", pci_name(pvt->F2));
	edac_dbg(1, "F3: %s\n", pci_name(pvt->F3));

	return 0;
}