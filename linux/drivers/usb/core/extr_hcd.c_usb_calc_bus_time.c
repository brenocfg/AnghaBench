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

/* Variables and functions */
 int /*<<< orphan*/  BW_HOST_DELAY ; 
 int BW_HUB_LS_SETUP ; 
 long BitTime (int) ; 
 unsigned long HS_NSECS (int) ; 
 unsigned long HS_NSECS_ISO (int) ; 
#define  USB_SPEED_FULL 130 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbcore_name ; 

long usb_calc_bus_time (int speed, int is_input, int isoc, int bytecount)
{
	unsigned long	tmp;

	switch (speed) {
	case USB_SPEED_LOW: 	/* INTR only */
		if (is_input) {
			tmp = (67667L * (31L + 10L * BitTime (bytecount))) / 1000L;
			return 64060L + (2 * BW_HUB_LS_SETUP) + BW_HOST_DELAY + tmp;
		} else {
			tmp = (66700L * (31L + 10L * BitTime (bytecount))) / 1000L;
			return 64107L + (2 * BW_HUB_LS_SETUP) + BW_HOST_DELAY + tmp;
		}
	case USB_SPEED_FULL:	/* ISOC or INTR */
		if (isoc) {
			tmp = (8354L * (31L + 10L * BitTime (bytecount))) / 1000L;
			return ((is_input) ? 7268L : 6265L) + BW_HOST_DELAY + tmp;
		} else {
			tmp = (8354L * (31L + 10L * BitTime (bytecount))) / 1000L;
			return 9107L + BW_HOST_DELAY + tmp;
		}
	case USB_SPEED_HIGH:	/* ISOC or INTR */
		/* FIXME adjust for input vs output */
		if (isoc)
			tmp = HS_NSECS_ISO (bytecount);
		else
			tmp = HS_NSECS (bytecount);
		return tmp;
	default:
		pr_debug ("%s: bogus device speed!\n", usbcore_name);
		return -1;
	}
}