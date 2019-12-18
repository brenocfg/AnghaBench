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
struct usb_composite_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_uvc ; 
 int /*<<< orphan*/  fi_uvc ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
webcam_unbind(struct usb_composite_dev *cdev)
{
	if (!IS_ERR_OR_NULL(f_uvc))
		usb_put_function(f_uvc);
	if (!IS_ERR_OR_NULL(fi_uvc))
		usb_put_function_instance(fi_uvc);
	return 0;
}