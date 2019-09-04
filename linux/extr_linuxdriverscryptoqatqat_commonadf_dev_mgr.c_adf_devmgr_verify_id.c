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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ ADF_CFG_ALL_DEVICES ; 
 int ENODEV ; 
 scalar_t__ adf_devmgr_get_dev_by_id (scalar_t__) ; 

int adf_devmgr_verify_id(uint32_t id)
{
	if (id == ADF_CFG_ALL_DEVICES)
		return 0;

	if (adf_devmgr_get_dev_by_id(id))
		return 0;

	return -ENODEV;
}