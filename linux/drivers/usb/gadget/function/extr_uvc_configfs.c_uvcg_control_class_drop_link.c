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
struct uvcg_control_header {int /*<<< orphan*/  linked; } ;
struct uvc_descriptor_header {int dummy; } ;
struct mutex {int dummy; } ;
struct f_uvc_opts {struct mutex lock; scalar_t__ refcnt; } ;
struct config_item {struct config_item* ci_parent; TYPE_2__* ci_group; } ;
struct TYPE_4__ {TYPE_1__* cg_subsys; } ;
struct TYPE_3__ {struct mutex su_mutex; } ;

/* Variables and functions */
 struct config_item* config_group_find_item (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 
 struct uvcg_control_header* to_uvcg_control_header (struct config_item*) ; 
 struct uvc_descriptor_header** uvcg_get_ctl_class_arr (struct config_item*,struct f_uvc_opts*) ; 

__attribute__((used)) static void uvcg_control_class_drop_link(struct config_item *src,
					struct config_item *target)
{
	struct config_item *control, *header;
	struct f_uvc_opts *opts;
	struct mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	struct uvc_descriptor_header **class_array;
	struct uvcg_control_header *target_hdr;

	mutex_lock(su_mutex); /* for navigating configfs hierarchy */

	control = src->ci_parent->ci_parent;
	header = config_group_find_item(to_config_group(control), "header");
	if (!header || target->ci_parent != header)
		goto out;

	opts = to_f_uvc_opts(control->ci_parent);

	mutex_lock(&opts->lock);

	class_array = uvcg_get_ctl_class_arr(src, opts);
	if (!class_array || opts->refcnt)
		goto unlock;

	target_hdr = to_uvcg_control_header(target);
	--target_hdr->linked;
	class_array[0] = NULL;

unlock:
	mutex_unlock(&opts->lock);
out:
	config_item_put(header);
	mutex_unlock(su_mutex);
}