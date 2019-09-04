#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct ocrdma_dev {TYPE_2__ nic_info; } ;
struct TYPE_3__ {int device; } ;

/* Variables and functions */
 char* OC_NAME_SH ; 
 char* OC_NAME_UNKNOWN ; 
#define  OC_SKH_DEVICE_PF 129 
#define  OC_SKH_DEVICE_VF 128 

__attribute__((used)) static inline char *hca_name(struct ocrdma_dev *dev)
{
	switch (dev->nic_info.pdev->device) {
	case OC_SKH_DEVICE_PF:
	case OC_SKH_DEVICE_VF:
		return OC_NAME_SH;
	default:
		return OC_NAME_UNKNOWN;
	}
}