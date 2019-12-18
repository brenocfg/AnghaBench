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
struct device_node {int dummy; } ;
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;

/* Variables and functions */
 int NUM_OF_PHYS ; 
 int USB_DR_MODE_UNKNOWN ; 
 int of_usb_get_dr_mode_by_phy (struct device_node*,int) ; 

__attribute__((used)) static enum usb_dr_mode rcar_gen3_get_dr_mode(struct device_node *np)
{
	enum usb_dr_mode candidate = USB_DR_MODE_UNKNOWN;
	int i;

	/*
	 * If one of device nodes has other dr_mode except UNKNOWN,
	 * this function returns UNKNOWN. To achieve backward compatibility,
	 * this loop starts the index as 0.
	 */
	for (i = 0; i < NUM_OF_PHYS; i++) {
		enum usb_dr_mode mode = of_usb_get_dr_mode_by_phy(np, i);

		if (mode != USB_DR_MODE_UNKNOWN) {
			if (candidate == USB_DR_MODE_UNKNOWN)
				candidate = mode;
			else if (candidate != mode)
				return USB_DR_MODE_UNKNOWN;
		}
	}

	return candidate;
}