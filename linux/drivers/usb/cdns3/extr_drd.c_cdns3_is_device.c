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
struct cdns3 {scalar_t__ dr_mode; } ;

/* Variables and functions */
 scalar_t__ USB_DR_MODE_OTG ; 
 scalar_t__ USB_DR_MODE_PERIPHERAL ; 
 scalar_t__ cdns3_get_id (struct cdns3*) ; 

int cdns3_is_device(struct cdns3 *cdns)
{
	if (cdns->dr_mode == USB_DR_MODE_PERIPHERAL)
		return 1;
	else if (cdns->dr_mode == USB_DR_MODE_OTG)
		if (cdns3_get_id(cdns))
			return 1;

	return 0;
}