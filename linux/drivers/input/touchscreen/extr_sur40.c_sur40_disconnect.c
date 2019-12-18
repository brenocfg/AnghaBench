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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct sur40_state {struct sur40_state* bulk_in_buffer; int /*<<< orphan*/  input; int /*<<< orphan*/  v4l2; int /*<<< orphan*/  vdev; int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_DESC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sur40_state*) ; 
 struct sur40_state* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sur40_disconnect(struct usb_interface *interface)
{
	struct sur40_state *sur40 = usb_get_intfdata(interface);

	v4l2_ctrl_handler_free(&sur40->hdl);
	video_unregister_device(&sur40->vdev);
	v4l2_device_unregister(&sur40->v4l2);

	input_unregister_polled_device(sur40->input);
	input_free_polled_device(sur40->input);
	kfree(sur40->bulk_in_buffer);
	kfree(sur40);

	usb_set_intfdata(interface, NULL);
	dev_dbg(&interface->dev, "%s is now disconnected\n", DRIVER_DESC);
}