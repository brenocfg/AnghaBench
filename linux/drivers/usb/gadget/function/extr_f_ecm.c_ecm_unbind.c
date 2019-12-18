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
struct usb_function {int dummy; } ;
struct usb_configuration {int /*<<< orphan*/  cdev; } ;
struct f_ecm {TYPE_1__* notify_req; int /*<<< orphan*/  notify; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 struct f_ecm* func_to_ecm (struct usb_function*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 

__attribute__((used)) static void ecm_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct f_ecm		*ecm = func_to_ecm(f);

	DBG(c->cdev, "ecm unbind\n");

	usb_free_all_descriptors(f);

	kfree(ecm->notify_req->buf);
	usb_ep_free_request(ecm->notify, ecm->notify_req);
}