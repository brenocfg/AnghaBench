#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct dev_data {TYPE_2__* req; TYPE_1__* config; TYPE_1__* hs_config; TYPE_3__* gadget; } ;
struct TYPE_6__ {scalar_t__ speed; } ;
struct TYPE_5__ {TYPE_1__* buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  wTotalLength; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ USB_DT_OTHER_SPEED_CONFIG ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ gadget_is_dualspeed (TYPE_3__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
config_buf (struct dev_data *dev, u8 type, unsigned index)
{
	int		len;
	int		hs = 0;

	/* only one configuration */
	if (index > 0)
		return -EINVAL;

	if (gadget_is_dualspeed(dev->gadget)) {
		hs = (dev->gadget->speed == USB_SPEED_HIGH);
		if (type == USB_DT_OTHER_SPEED_CONFIG)
			hs = !hs;
	}
	if (hs) {
		dev->req->buf = dev->hs_config;
		len = le16_to_cpu(dev->hs_config->wTotalLength);
	} else {
		dev->req->buf = dev->config;
		len = le16_to_cpu(dev->config->wTotalLength);
	}
	((u8 *)dev->req->buf) [1] = type;
	return len;
}