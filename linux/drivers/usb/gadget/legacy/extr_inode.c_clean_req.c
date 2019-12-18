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
struct usb_request {scalar_t__ buf; int /*<<< orphan*/  complete; } ;
struct usb_ep {struct dev_data* driver_data; } ;
struct dev_data {scalar_t__ rbuf; scalar_t__ setup_out_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  epio_complete ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static void clean_req (struct usb_ep *ep, struct usb_request *req)
{
	struct dev_data		*dev = ep->driver_data;

	if (req->buf != dev->rbuf) {
		kfree(req->buf);
		req->buf = dev->rbuf;
	}
	req->complete = epio_complete;
	dev->setup_out_ready = 0;
}