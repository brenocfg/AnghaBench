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
struct usb_hcd {int dummy; } ;
struct gbphy_device {int dummy; } ;
struct gb_usb_device {struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 struct gb_usb_device* gb_gbphy_get_data (struct gbphy_device*) ; 
 struct usb_hcd* gb_usb_device_to_hcd (struct gb_usb_device*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static void gb_usb_remove(struct gbphy_device *gbphy_dev)
{
	struct gb_usb_device *gb_usb_dev = gb_gbphy_get_data(gbphy_dev);
	struct gb_connection *connection = gb_usb_dev->connection;
	struct usb_hcd *hcd = gb_usb_device_to_hcd(gb_usb_dev);

	usb_remove_hcd(hcd);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
	usb_put_hcd(hcd);
}