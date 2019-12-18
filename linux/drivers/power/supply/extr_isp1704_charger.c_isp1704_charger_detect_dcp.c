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
struct isp1704_charger {int dummy; } ;

/* Variables and functions */
 scalar_t__ POWER_SUPPLY_TYPE_USB_DCP ; 
 scalar_t__ isp1704_charger_detect (struct isp1704_charger*) ; 
 scalar_t__ isp1704_charger_type (struct isp1704_charger*) ; 

__attribute__((used)) static inline int isp1704_charger_detect_dcp(struct isp1704_charger *isp)
{
	if (isp1704_charger_detect(isp) &&
			isp1704_charger_type(isp) == POWER_SUPPLY_TYPE_USB_DCP)
		return true;
	else
		return false;
}