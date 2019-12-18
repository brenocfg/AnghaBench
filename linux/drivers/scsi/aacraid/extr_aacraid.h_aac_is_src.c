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
typedef  scalar_t__ u16 ;
struct aac_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PMC_DEVICE_S6 ; 
 scalar_t__ PMC_DEVICE_S7 ; 
 scalar_t__ PMC_DEVICE_S8 ; 

__attribute__((used)) static inline int aac_is_src(struct aac_dev *dev)
{
	u16 device = dev->pdev->device;

	if (device == PMC_DEVICE_S6 ||
		device == PMC_DEVICE_S7 ||
		device == PMC_DEVICE_S8)
		return 1;
	return 0;
}