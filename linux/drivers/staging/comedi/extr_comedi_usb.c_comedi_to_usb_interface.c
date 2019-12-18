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
struct comedi_device {scalar_t__ hw_dev; } ;

/* Variables and functions */
 struct usb_interface* to_usb_interface (scalar_t__) ; 

struct usb_interface *comedi_to_usb_interface(struct comedi_device *dev)
{
	return dev->hw_dev ? to_usb_interface(dev->hw_dev) : NULL;
}