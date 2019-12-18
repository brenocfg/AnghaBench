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
struct cdns3_endpoint {int type; } ;

/* Variables and functions */
 int TRB_CTRL_RING_SIZE ; 
 int TRB_ISO_RING_SIZE ; 
 int TRB_RING_SIZE ; 
#define  USB_ENDPOINT_XFER_CONTROL 129 
#define  USB_ENDPOINT_XFER_ISOC 128 

int cdns3_ring_size(struct cdns3_endpoint *priv_ep)
{
	switch (priv_ep->type) {
	case USB_ENDPOINT_XFER_ISOC:
		return TRB_ISO_RING_SIZE;
	case USB_ENDPOINT_XFER_CONTROL:
		return TRB_CTRL_RING_SIZE;
	default:
		return TRB_RING_SIZE;
	}
}