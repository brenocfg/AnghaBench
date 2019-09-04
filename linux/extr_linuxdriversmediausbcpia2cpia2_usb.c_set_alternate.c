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
struct camera_data {unsigned int cur_alt; unsigned int old_alt; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned int,unsigned int) ; 
 unsigned int USBIF_CMDONLY ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int set_alternate(struct camera_data *cam, unsigned int alt)
{
	int ret = 0;

	if(alt == cam->cur_alt)
		return 0;

	if (cam->cur_alt != USBIF_CMDONLY) {
		DBG("Changing from alt %d to %d\n", cam->cur_alt, USBIF_CMDONLY);
		ret = usb_set_interface(cam->dev, cam->iface, USBIF_CMDONLY);
		if (ret != 0)
			return ret;
	}
	if (alt != USBIF_CMDONLY) {
		DBG("Changing from alt %d to %d\n", USBIF_CMDONLY, alt);
		ret = usb_set_interface(cam->dev, cam->iface, alt);
		if (ret != 0)
			return ret;
	}

	cam->old_alt = cam->cur_alt;
	cam->cur_alt = alt;

	return ret;
}