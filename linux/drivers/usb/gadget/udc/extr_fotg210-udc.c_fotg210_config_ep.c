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
struct usb_endpoint_descriptor {int dummy; } ;
struct fotg210_udc {struct fotg210_ep** ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  maxpacket; } ;
struct fotg210_ep {size_t epnum; int /*<<< orphan*/  dir_in; TYPE_1__ ep; int /*<<< orphan*/  type; struct fotg210_udc* fotg210; } ;

/* Variables and functions */
 int /*<<< orphan*/  fotg210_fifo_ep_mapping (struct fotg210_ep*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fotg210_set_fifo_dir (struct fotg210_ep*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fotg210_set_mps (struct fotg210_ep*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fotg210_set_tfrtype (struct fotg210_ep*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fotg210_config_ep(struct fotg210_ep *ep,
		     const struct usb_endpoint_descriptor *desc)
{
	struct fotg210_udc *fotg210 = ep->fotg210;

	fotg210_set_fifo_dir(ep, ep->epnum, ep->dir_in);
	fotg210_set_tfrtype(ep, ep->epnum, ep->type);
	fotg210_set_mps(ep, ep->epnum, ep->ep.maxpacket, ep->dir_in);
	fotg210_fifo_ep_mapping(ep, ep->epnum, ep->dir_in);

	fotg210->ep[ep->epnum] = ep;

	return 0;
}