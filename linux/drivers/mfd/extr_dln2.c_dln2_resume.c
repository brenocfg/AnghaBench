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
struct dln2_dev {int disconnect; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int dln2_start_rx_urbs (struct dln2_dev*,int /*<<< orphan*/ ) ; 
 struct dln2_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int dln2_resume(struct usb_interface *iface)
{
	struct dln2_dev *dln2 = usb_get_intfdata(iface);

	dln2->disconnect = false;

	return dln2_start_rx_urbs(dln2, GFP_NOIO);
}