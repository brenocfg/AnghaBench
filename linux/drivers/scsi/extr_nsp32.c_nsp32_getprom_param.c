#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pci_devid; } ;
typedef  TYPE_2__ nsp32_hw_data ;
struct TYPE_7__ {int vendor; int device; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  NSP32_DEBUG_EEPROM ; 
 int PCI_DEVICE_ID_NINJASCSI_32BIB_LOGITEC ; 
 int PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO ; 
 int PCI_DEVICE_ID_WORKBIT_STANDARD ; 
 int PCI_VENDOR_ID_WORKBIT ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int nsp32_getprom_at24 (TYPE_2__*) ; 
 int nsp32_getprom_c16 (TYPE_2__*) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*,...) ; 
 int nsp32_prom_read (TYPE_2__*,int) ; 

__attribute__((used)) static int nsp32_getprom_param(nsp32_hw_data *data)
{
	int vendor = data->pci_devid->vendor;
	int device = data->pci_devid->device;
	int ret, val, i;

	/*
	 * EEPROM checking.
	 */
	ret = nsp32_prom_read(data, 0x7e);
	if (ret != 0x55) {
		nsp32_msg(KERN_INFO, "No EEPROM detected: 0x%x", ret);
		return FALSE;
	}
	ret = nsp32_prom_read(data, 0x7f);
	if (ret != 0xaa) {
		nsp32_msg(KERN_INFO, "Invalid number: 0x%x", ret);
		return FALSE;
	}

	/*
	 * check EEPROM type
	 */
	if (vendor == PCI_VENDOR_ID_WORKBIT &&
	    device == PCI_DEVICE_ID_WORKBIT_STANDARD) {
		ret = nsp32_getprom_c16(data);
	} else if (vendor == PCI_VENDOR_ID_WORKBIT &&
		   device == PCI_DEVICE_ID_NINJASCSI_32BIB_LOGITEC) {
		ret = nsp32_getprom_at24(data);
	} else if (vendor == PCI_VENDOR_ID_WORKBIT &&
		   device == PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO ) {
		ret = nsp32_getprom_at24(data);
	} else {
		nsp32_msg(KERN_WARNING, "Unknown EEPROM");
		ret = FALSE;
	}

	/* for debug : SPROM data full checking */
	for (i = 0; i <= 0x1f; i++) {
		val = nsp32_prom_read(data, i);
		nsp32_dbg(NSP32_DEBUG_EEPROM,
			  "rom address 0x%x : 0x%x", i, val);
	}

	return ret;
}