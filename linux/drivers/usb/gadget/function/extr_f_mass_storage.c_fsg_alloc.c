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
struct usb_function_instance {int dummy; } ;
struct usb_function {int /*<<< orphan*/  free_func; int /*<<< orphan*/  disable; int /*<<< orphan*/  set_alt; int /*<<< orphan*/  setup; int /*<<< orphan*/  unbind; int /*<<< orphan*/  bind; int /*<<< orphan*/  name; } ;
struct fsg_opts {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; struct fsg_common* common; } ;
struct fsg_dev {struct usb_function function; struct fsg_common* common; } ;
struct fsg_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSG_DRIVER_DESC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fsg_bind ; 
 int /*<<< orphan*/  fsg_disable ; 
 int /*<<< orphan*/  fsg_free ; 
 struct fsg_opts* fsg_opts_from_func_inst (struct usb_function_instance*) ; 
 int /*<<< orphan*/  fsg_set_alt ; 
 int /*<<< orphan*/  fsg_setup ; 
 int /*<<< orphan*/  fsg_unbind ; 
 struct fsg_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct usb_function *fsg_alloc(struct usb_function_instance *fi)
{
	struct fsg_opts *opts = fsg_opts_from_func_inst(fi);
	struct fsg_common *common = opts->common;
	struct fsg_dev *fsg;

	fsg = kzalloc(sizeof(*fsg), GFP_KERNEL);
	if (unlikely(!fsg))
		return ERR_PTR(-ENOMEM);

	mutex_lock(&opts->lock);
	opts->refcnt++;
	mutex_unlock(&opts->lock);

	fsg->function.name	= FSG_DRIVER_DESC;
	fsg->function.bind	= fsg_bind;
	fsg->function.unbind	= fsg_unbind;
	fsg->function.setup	= fsg_setup;
	fsg->function.set_alt	= fsg_set_alt;
	fsg->function.disable	= fsg_disable;
	fsg->function.free_func	= fsg_free;

	fsg->common               = common;

	return &fsg->function;
}