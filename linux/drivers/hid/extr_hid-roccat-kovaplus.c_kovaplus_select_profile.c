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
typedef  int /*<<< orphan*/  uint ;
struct usb_device {int dummy; } ;
typedef  enum kovaplus_control_requests { ____Placeholder_kovaplus_control_requests } kovaplus_control_requests ;

/* Variables and functions */
 int kovaplus_send_control (struct usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kovaplus_select_profile(struct usb_device *usb_dev, uint number,
		enum kovaplus_control_requests request)
{
	return kovaplus_send_control(usb_dev, number, request);
}