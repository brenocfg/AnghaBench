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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_VORTEX_GDT6555 ; 
 scalar_t__ PCI_DEVICE_ID_VORTEX_GDT6x17RP ; 
 scalar_t__ PCI_DEVICE_ID_VORTEX_GDTMAXRP ; 
 scalar_t__ PCI_DEVICE_ID_VORTEX_GDTNEWRX ; 
 scalar_t__ PCI_DEVICE_ID_VORTEX_GDTNEWRX2 ; 

__attribute__((used)) static bool gdth_search_vortex(u16 device)
{
	if (device <= PCI_DEVICE_ID_VORTEX_GDT6555)
		return true;
	if (device >= PCI_DEVICE_ID_VORTEX_GDT6x17RP &&
	    device <= PCI_DEVICE_ID_VORTEX_GDTMAXRP)
		return true;
	if (device == PCI_DEVICE_ID_VORTEX_GDTNEWRX ||
	    device == PCI_DEVICE_ID_VORTEX_GDTNEWRX2)
		return true;
	return false;
}