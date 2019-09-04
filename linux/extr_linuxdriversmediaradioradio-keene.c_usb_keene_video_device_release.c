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
struct keene_device {struct keene_device* buffer; int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct keene_device*) ; 
 struct keene_device* to_keene_dev (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_keene_video_device_release(struct v4l2_device *v4l2_dev)
{
	struct keene_device *radio = to_keene_dev(v4l2_dev);

	/* free rest memory */
	v4l2_ctrl_handler_free(&radio->hdl);
	kfree(radio->buffer);
	kfree(radio);
}