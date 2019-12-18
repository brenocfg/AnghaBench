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
struct usb_configuration {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_uvc ; 
 int /*<<< orphan*/  fi_uvc ; 
 int usb_add_function (struct usb_configuration*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
webcam_config_bind(struct usb_configuration *c)
{
	int status = 0;

	f_uvc = usb_get_function(fi_uvc);
	if (IS_ERR(f_uvc))
		return PTR_ERR(f_uvc);

	status = usb_add_function(c, f_uvc);
	if (status < 0)
		usb_put_function(f_uvc);

	return status;
}