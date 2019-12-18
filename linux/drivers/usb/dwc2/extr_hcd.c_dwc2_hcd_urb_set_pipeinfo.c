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
typedef  scalar_t__ u8 ;
typedef  void* u16 ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {void* maxp_mult; void* maxp; scalar_t__ pipe_dir; scalar_t__ pipe_type; scalar_t__ ep_num; scalar_t__ dev_addr; } ;
struct dwc2_hcd_urb {TYPE_1__ pipe_info; } ;

/* Variables and functions */
 scalar_t__ USB_ENDPOINT_XFER_BULK ; 
 scalar_t__ USB_ENDPOINT_XFER_CONTROL ; 
 scalar_t__ dbg_perio () ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,void*) ; 

__attribute__((used)) static void dwc2_hcd_urb_set_pipeinfo(struct dwc2_hsotg *hsotg,
				      struct dwc2_hcd_urb *urb, u8 dev_addr,
				      u8 ep_num, u8 ep_type, u8 ep_dir,
				      u16 maxp, u16 maxp_mult)
{
	if (dbg_perio() ||
	    ep_type == USB_ENDPOINT_XFER_BULK ||
	    ep_type == USB_ENDPOINT_XFER_CONTROL)
		dev_vdbg(hsotg->dev,
			 "addr=%d, ep_num=%d, ep_dir=%1x, ep_type=%1x, maxp=%d (%d mult)\n",
			 dev_addr, ep_num, ep_dir, ep_type, maxp, maxp_mult);
	urb->pipe_info.dev_addr = dev_addr;
	urb->pipe_info.ep_num = ep_num;
	urb->pipe_info.pipe_type = ep_type;
	urb->pipe_info.pipe_dir = ep_dir;
	urb->pipe_info.maxp = maxp;
	urb->pipe_info.maxp_mult = maxp_mult;
}