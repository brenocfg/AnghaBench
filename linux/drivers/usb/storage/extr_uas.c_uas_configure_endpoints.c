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
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_device {scalar_t__ speed; } ;
struct uas_dev_info {int qdepth; int use_streams; TYPE_1__* intf; void* data_out_pipe; void* data_in_pipe; void* status_pipe; void* cmd_pipe; struct usb_device* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cur_altsetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  MAX_CMNDS ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int uas_find_endpoints (int /*<<< orphan*/ ,struct usb_host_endpoint**) ; 
 int usb_alloc_streams (TYPE_1__*,struct usb_host_endpoint**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_num (int /*<<< orphan*/ *) ; 
 void* usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 void* usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uas_configure_endpoints(struct uas_dev_info *devinfo)
{
	struct usb_host_endpoint *eps[4] = { };
	struct usb_device *udev = devinfo->udev;
	int r;

	r = uas_find_endpoints(devinfo->intf->cur_altsetting, eps);
	if (r)
		return r;

	devinfo->cmd_pipe = usb_sndbulkpipe(udev,
					    usb_endpoint_num(&eps[0]->desc));
	devinfo->status_pipe = usb_rcvbulkpipe(udev,
					    usb_endpoint_num(&eps[1]->desc));
	devinfo->data_in_pipe = usb_rcvbulkpipe(udev,
					    usb_endpoint_num(&eps[2]->desc));
	devinfo->data_out_pipe = usb_sndbulkpipe(udev,
					    usb_endpoint_num(&eps[3]->desc));

	if (udev->speed < USB_SPEED_SUPER) {
		devinfo->qdepth = 32;
		devinfo->use_streams = 0;
	} else {
		devinfo->qdepth = usb_alloc_streams(devinfo->intf, eps + 1,
						    3, MAX_CMNDS, GFP_NOIO);
		if (devinfo->qdepth < 0)
			return devinfo->qdepth;
		devinfo->use_streams = 1;
	}

	return 0;
}