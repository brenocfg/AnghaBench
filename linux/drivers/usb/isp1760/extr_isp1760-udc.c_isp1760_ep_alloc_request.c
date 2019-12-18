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
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;
struct isp1760_request {struct usb_request req; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct isp1760_request* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_request *isp1760_ep_alloc_request(struct usb_ep *ep,
						    gfp_t gfp_flags)
{
	struct isp1760_request *req;

	req = kzalloc(sizeof(*req), gfp_flags);
	if (!req)
		return NULL;

	return &req->req;
}