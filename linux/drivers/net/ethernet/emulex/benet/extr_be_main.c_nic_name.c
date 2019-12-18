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
struct pci_dev {int device; } ;

/* Variables and functions */
 char* BE3_NAME ; 
#define  BE_DEVICE_ID2 134 
 char* BE_NAME ; 
#define  OC_DEVICE_ID1 133 
#define  OC_DEVICE_ID2 132 
#define  OC_DEVICE_ID3 131 
#define  OC_DEVICE_ID4 130 
#define  OC_DEVICE_ID5 129 
#define  OC_DEVICE_ID6 128 
 char* OC_NAME ; 
 char* OC_NAME_BE ; 
 char* OC_NAME_LANCER ; 
 char* OC_NAME_SH ; 

__attribute__((used)) static inline char *nic_name(struct pci_dev *pdev)
{
	switch (pdev->device) {
	case OC_DEVICE_ID1:
		return OC_NAME;
	case OC_DEVICE_ID2:
		return OC_NAME_BE;
	case OC_DEVICE_ID3:
	case OC_DEVICE_ID4:
		return OC_NAME_LANCER;
	case BE_DEVICE_ID2:
		return BE3_NAME;
	case OC_DEVICE_ID5:
	case OC_DEVICE_ID6:
		return OC_NAME_SH;
	default:
		return BE_NAME;
	}
}