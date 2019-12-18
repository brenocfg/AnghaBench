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
struct usb_function {scalar_t__ os_desc_n; int /*<<< orphan*/  os_desc_table; } ;
struct usb_configuration {int /*<<< orphan*/  cdev; } ;
struct f_ncm {TYPE_1__* notify_req; int /*<<< orphan*/  notify; int /*<<< orphan*/  task_timer; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 struct f_ncm* func_to_ncm (struct usb_function*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 TYPE_2__* ncm_string_defs ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 

__attribute__((used)) static void ncm_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct f_ncm *ncm = func_to_ncm(f);

	DBG(c->cdev, "ncm unbind\n");

	hrtimer_cancel(&ncm->task_timer);

	kfree(f->os_desc_table);
	f->os_desc_n = 0;

	ncm_string_defs[0].id = 0;
	usb_free_all_descriptors(f);

	kfree(ncm->notify_req->buf);
	usb_ep_free_request(ncm->notify, ncm->notify_req);
}