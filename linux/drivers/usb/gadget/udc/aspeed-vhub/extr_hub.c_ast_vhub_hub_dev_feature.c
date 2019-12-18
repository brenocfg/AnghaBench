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
typedef  scalar_t__ u16 ;
struct ast_vhub_ep {TYPE_1__* vhub; } ;
struct TYPE_2__ {int wakeup_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*,char*,...) ; 
 scalar_t__ USB_DEVICE_REMOTE_WAKEUP ; 
 int std_req_complete ; 
 int std_req_stall ; 

__attribute__((used)) static int ast_vhub_hub_dev_feature(struct ast_vhub_ep *ep,
				    u16 wIndex, u16 wValue,
				    bool is_set)
{
	EPDBG(ep, "%s_FEATURE(dev val=%02x)\n",
	      is_set ? "SET" : "CLEAR", wValue);

	if (wValue != USB_DEVICE_REMOTE_WAKEUP)
		return std_req_stall;

	ep->vhub->wakeup_en = is_set;
	EPDBG(ep, "Hub remote wakeup %s\n",
	      is_set ? "enabled" : "disabled");

	return std_req_complete;
}