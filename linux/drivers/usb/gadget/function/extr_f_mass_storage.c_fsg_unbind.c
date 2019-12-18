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
struct usb_function {int dummy; } ;
struct usb_configuration {int dummy; } ;
struct fsg_dev {int /*<<< orphan*/  function; struct fsg_common* common; } ;
struct fsg_common {struct fsg_dev* fsg; int /*<<< orphan*/  fsg_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*) ; 
 int /*<<< orphan*/  FSG_STATE_CONFIG_CHANGE ; 
 int /*<<< orphan*/  __raise_exception (struct fsg_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fsg_dev* fsg_from_func (struct usb_function*) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fsg_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct fsg_dev		*fsg = fsg_from_func(f);
	struct fsg_common	*common = fsg->common;

	DBG(fsg, "unbind\n");
	if (fsg->common->fsg == fsg) {
		__raise_exception(fsg->common, FSG_STATE_CONFIG_CHANGE, NULL);
		/* FIXME: make interruptible or killable somehow? */
		wait_event(common->fsg_wait, common->fsg != fsg);
	}

	usb_free_all_descriptors(&fsg->function);
}