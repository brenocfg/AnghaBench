#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usbnet {TYPE_2__* driver_info; int /*<<< orphan*/  data; } ;
struct rndis_indicate {int /*<<< orphan*/  status; } ;
struct device {int dummy; } ;
struct cdc_state {TYPE_1__* control; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* indication ) (struct usbnet*,struct rndis_indicate*,int) ;} ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
#define  RNDIS_STATUS_MEDIA_CONNECT 129 
#define  RNDIS_STATUS_MEDIA_DISCONNECT 128 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usbnet*,struct rndis_indicate*,int) ; 

__attribute__((used)) static void rndis_msg_indicate(struct usbnet *dev, struct rndis_indicate *msg,
				int buflen)
{
	struct cdc_state *info = (void *)&dev->data;
	struct device *udev = &info->control->dev;

	if (dev->driver_info->indication) {
		dev->driver_info->indication(dev, msg, buflen);
	} else {
		u32 status = le32_to_cpu(msg->status);

		switch (status) {
		case RNDIS_STATUS_MEDIA_CONNECT:
			dev_info(udev, "rndis media connect\n");
			break;
		case RNDIS_STATUS_MEDIA_DISCONNECT:
			dev_info(udev, "rndis media disconnect\n");
			break;
		default:
			dev_info(udev, "rndis indication: 0x%08x\n", status);
		}
	}
}