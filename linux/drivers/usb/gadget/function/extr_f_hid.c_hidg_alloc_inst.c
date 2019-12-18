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
struct usb_function_instance {int /*<<< orphan*/  group; int /*<<< orphan*/  free_func_inst; } ;
struct f_hid_opts {scalar_t__ minor; struct usb_function_instance func_inst; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct usb_function_instance* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIDG_MINORS ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghid_cleanup () ; 
 int ghid_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_func_type ; 
 int /*<<< orphan*/  hidg_free_inst ; 
 scalar_t__ hidg_get_minor () ; 
 int /*<<< orphan*/  hidg_ida ; 
 int /*<<< orphan*/  hidg_ida_lock ; 
 scalar_t__ ida_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct f_hid_opts*) ; 
 struct f_hid_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct usb_function_instance *hidg_alloc_inst(void)
{
	struct f_hid_opts *opts;
	struct usb_function_instance *ret;
	int status = 0;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);
	mutex_init(&opts->lock);
	opts->func_inst.free_func_inst = hidg_free_inst;
	ret = &opts->func_inst;

	mutex_lock(&hidg_ida_lock);

	if (ida_is_empty(&hidg_ida)) {
		status = ghid_setup(NULL, HIDG_MINORS);
		if (status)  {
			ret = ERR_PTR(status);
			kfree(opts);
			goto unlock;
		}
	}

	opts->minor = hidg_get_minor();
	if (opts->minor < 0) {
		ret = ERR_PTR(opts->minor);
		kfree(opts);
		if (ida_is_empty(&hidg_ida))
			ghid_cleanup();
		goto unlock;
	}
	config_group_init_type_name(&opts->func_inst.group, "", &hid_func_type);

unlock:
	mutex_unlock(&hidg_ida_lock);
	return ret;
}