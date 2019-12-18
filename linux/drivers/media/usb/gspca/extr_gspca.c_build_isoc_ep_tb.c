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
struct usb_interface {int num_altsetting; int /*<<< orphan*/ * altsetting; } ;
struct TYPE_3__ {int bInterval; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_host_endpoint {TYPE_1__ desc; } ;
struct gspca_dev {TYPE_2__* dev; scalar_t__ audio; int /*<<< orphan*/  xfer_ep; } ;
struct ep_tb_s {int bandwidth; int alt; } ;
struct TYPE_4__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int MAX_ALT ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_ISOC ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_SUPER ; 
 struct usb_host_endpoint* alt_xfer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int which_bandwidth (struct gspca_dev*) ; 

__attribute__((used)) static int build_isoc_ep_tb(struct gspca_dev *gspca_dev,
			struct usb_interface *intf,
			struct ep_tb_s *ep_tb)
{
	struct usb_host_endpoint *ep;
	int i, j, nbalt, psize, found;
	u32 bandwidth, last_bw;

	nbalt = intf->num_altsetting;
	if (nbalt > MAX_ALT)
		nbalt = MAX_ALT;	/* fixme: should warn */

	/* build the endpoint table */
	i = 0;
	last_bw = 0;
	for (;;) {
		ep_tb->bandwidth = 2000 * 2000 * 120;
		found = 0;
		for (j = 0; j < nbalt; j++) {
			ep = alt_xfer(&intf->altsetting[j],
				      USB_ENDPOINT_XFER_ISOC,
				      gspca_dev->xfer_ep);
			if (ep == NULL)
				continue;
			if (ep->desc.bInterval == 0) {
				pr_err("alt %d iso endp with 0 interval\n", j);
				continue;
			}
			psize = le16_to_cpu(ep->desc.wMaxPacketSize);
			psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
			bandwidth = psize * 1000;
			if (gspca_dev->dev->speed == USB_SPEED_HIGH
			 || gspca_dev->dev->speed >= USB_SPEED_SUPER)
				bandwidth *= 8;
			bandwidth /= 1 << (ep->desc.bInterval - 1);
			if (bandwidth <= last_bw)
				continue;
			if (bandwidth < ep_tb->bandwidth) {
				ep_tb->bandwidth = bandwidth;
				ep_tb->alt = j;
				found = 1;
			}
		}
		if (!found)
			break;
		gspca_dbg(gspca_dev, D_STREAM, "alt %d bandwidth %d\n",
			  ep_tb->alt, ep_tb->bandwidth);
		last_bw = ep_tb->bandwidth;
		i++;
		ep_tb++;
	}

	/*
	 * If the camera:
	 * has a usb audio class interface (a built in usb mic); and
	 * is a usb 1 full speed device; and
	 * uses the max full speed iso bandwidth; and
	 * and has more than 1 alt setting
	 * then skip the highest alt setting to spare bandwidth for the mic
	 */
	if (gspca_dev->audio &&
			gspca_dev->dev->speed == USB_SPEED_FULL &&
			last_bw >= 1000000 &&
			i > 1) {
		gspca_dbg(gspca_dev, D_STREAM, "dev has usb audio, skipping highest alt\n");
		i--;
		ep_tb--;
	}

	/* get the requested bandwidth and start at the highest atlsetting */
	bandwidth = which_bandwidth(gspca_dev);
	ep_tb--;
	while (i > 1) {
		ep_tb--;
		if (ep_tb->bandwidth < bandwidth)
			break;
		i--;
	}
	return i;
}