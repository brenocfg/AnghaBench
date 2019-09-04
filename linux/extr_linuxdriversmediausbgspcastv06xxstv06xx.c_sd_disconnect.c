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
struct usb_interface {int dummy; } ;
struct sd {int /*<<< orphan*/ * sensor; void* sensor_priv; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_disconnect (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 struct gspca_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void sd_disconnect(struct usb_interface *intf)
{
	struct gspca_dev *gspca_dev = usb_get_intfdata(intf);
	struct sd *sd = (struct sd *) gspca_dev;
	void *priv = sd->sensor_priv;
	gspca_dbg(gspca_dev, D_PROBE, "Disconnecting the stv06xx device\n");

	sd->sensor = NULL;
	gspca_disconnect(intf);
	kfree(priv);
}