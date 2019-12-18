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
struct renesas_usb3_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct renesas_usb3_request*) ; 
 struct renesas_usb3_request* usb_req_to_usb3_req (struct usb_request*) ; 

__attribute__((used)) static void __renesas_usb3_ep_free_request(struct usb_request *_req)
{
	struct renesas_usb3_request *usb3_req = usb_req_to_usb3_req(_req);

	kfree(usb3_req);
}