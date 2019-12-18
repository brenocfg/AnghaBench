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
struct usb_xpad {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct usb_xpad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  xpad_stop_input (struct usb_xpad*) ; 

__attribute__((used)) static void xpad_close(struct input_dev *dev)
{
	struct usb_xpad *xpad = input_get_drvdata(dev);

	xpad_stop_input(xpad);
}