#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {int dummy; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct shark_device {int /*<<< orphan*/  v4l2_dev; TYPE_1__ tea; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shark_unregister_leds (struct shark_device*) ; 
 int /*<<< orphan*/  snd_tea575x_exit (TYPE_1__*) ; 
 struct v4l2_device* usb_get_intfdata (struct usb_interface*) ; 
 struct shark_device* v4l2_dev_to_shark (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_shark_disconnect(struct usb_interface *intf)
{
	struct v4l2_device *v4l2_dev = usb_get_intfdata(intf);
	struct shark_device *shark = v4l2_dev_to_shark(v4l2_dev);

	mutex_lock(&shark->tea.mutex);
	v4l2_device_disconnect(&shark->v4l2_dev);
	snd_tea575x_exit(&shark->tea);
	mutex_unlock(&shark->tea.mutex);

	shark_unregister_leds(shark);

	v4l2_device_put(&shark->v4l2_dev);
}