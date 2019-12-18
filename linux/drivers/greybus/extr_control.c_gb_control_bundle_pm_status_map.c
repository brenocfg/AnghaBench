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
typedef  int u8 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMSG ; 
 int EREMOTEIO ; 
#define  GB_CONTROL_BUNDLE_PM_BUSY 131 
#define  GB_CONTROL_BUNDLE_PM_FAIL 130 
#define  GB_CONTROL_BUNDLE_PM_INVAL 129 
#define  GB_CONTROL_BUNDLE_PM_NA 128 

__attribute__((used)) static int gb_control_bundle_pm_status_map(u8 status)
{
	switch (status) {
	case GB_CONTROL_BUNDLE_PM_INVAL:
		return -EINVAL;
	case GB_CONTROL_BUNDLE_PM_BUSY:
		return -EBUSY;
	case GB_CONTROL_BUNDLE_PM_NA:
		return -ENOMSG;
	case GB_CONTROL_BUNDLE_PM_FAIL:
	default:
		return -EREMOTEIO;
	}
}