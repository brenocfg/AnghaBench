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
struct v4l2_device {int dummy; } ;
struct ma901radio_device {struct ma901radio_device* buffer; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ma901radio_device*) ; 
 struct ma901radio_device* to_ma901radio_dev (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_ma901radio_release(struct v4l2_device *v4l2_dev)
{
	struct ma901radio_device *radio = to_ma901radio_dev(v4l2_dev);

	v4l2_ctrl_handler_free(&radio->hdl);
	v4l2_device_unregister(&radio->v4l2_dev);
	kfree(radio->buffer);
	kfree(radio);
}