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
struct usbatm_data {struct uea_softc* driver_data; } ;
struct usb_interface {int dummy; } ;
struct uea_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uea_softc*) ; 
 int /*<<< orphan*/  uea_stop (struct uea_softc*) ; 

__attribute__((used)) static void uea_unbind(struct usbatm_data *usbatm, struct usb_interface *intf)
{
	struct uea_softc *sc = usbatm->driver_data;

	uea_stop(sc);
	kfree(sc);
}