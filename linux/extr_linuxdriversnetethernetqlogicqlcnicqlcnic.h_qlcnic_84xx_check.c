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
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {unsigned short device; } ;

/* Variables and functions */
 unsigned short PCI_DEVICE_ID_QLOGIC_QLE844X ; 
 unsigned short PCI_DEVICE_ID_QLOGIC_VF_QLE844X ; 

__attribute__((used)) static inline bool qlcnic_84xx_check(struct qlcnic_adapter *adapter)
{
	unsigned short device = adapter->pdev->device;

	return ((device == PCI_DEVICE_ID_QLOGIC_QLE844X) ||
		(device == PCI_DEVICE_ID_QLOGIC_VF_QLE844X)) ? true : false;
}