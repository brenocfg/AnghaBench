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
struct usb_configuration {int dummy; } ;
struct f_acm {scalar_t__ notify_req; int /*<<< orphan*/  notify; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 TYPE_1__* acm_string_defs ; 
 struct f_acm* func_to_acm (struct usb_function*) ; 
 int /*<<< orphan*/  gs_free_req (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 

__attribute__((used)) static void acm_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct f_acm		*acm = func_to_acm(f);

	acm_string_defs[0].id = 0;
	usb_free_all_descriptors(f);
	if (acm->notify_req)
		gs_free_req(acm->notify, acm->notify_req);
}