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
struct usb_host_endpoint {int dummy; } ;
struct usb_device {int dummy; } ;
struct uas_dev_info {int /*<<< orphan*/  intf; int /*<<< orphan*/  data_out_pipe; int /*<<< orphan*/  data_in_pipe; int /*<<< orphan*/  status_pipe; struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  usb_free_streams (int /*<<< orphan*/ ,struct usb_host_endpoint**,int,int /*<<< orphan*/ ) ; 
 struct usb_host_endpoint* usb_pipe_endpoint (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uas_free_streams(struct uas_dev_info *devinfo)
{
	struct usb_device *udev = devinfo->udev;
	struct usb_host_endpoint *eps[3];

	eps[0] = usb_pipe_endpoint(udev, devinfo->status_pipe);
	eps[1] = usb_pipe_endpoint(udev, devinfo->data_in_pipe);
	eps[2] = usb_pipe_endpoint(udev, devinfo->data_out_pipe);
	usb_free_streams(devinfo->intf, eps, 3, GFP_NOIO);
}