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
struct uvcg_streaming_header {int /*<<< orphan*/  linked; } ;
typedef  int /*<<< orphan*/ **** uvc_descriptor_header ;
struct mutex {int dummy; } ;
struct f_uvc_opts {struct mutex lock; scalar_t__ refcnt; } ;
struct config_item {struct config_item* ci_parent; TYPE_2__* ci_group; } ;
struct TYPE_4__ {TYPE_1__* cg_subsys; } ;
struct TYPE_3__ {struct mutex su_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/ ********* __uvcg_get_stream_class_arr (struct config_item*,struct f_uvc_opts*) ; 
 struct config_item* config_group_find_item (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ******) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 
 struct uvcg_streaming_header* to_uvcg_streaming_header (struct config_item*) ; 

__attribute__((used)) static void uvcg_streaming_class_drop_link(struct config_item *src,
					  struct config_item *target)
{
	struct config_item *streaming, *header;
	struct f_uvc_opts *opts;
	struct mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	struct uvc_descriptor_header ***class_array;
	struct uvcg_streaming_header *target_hdr;

	mutex_lock(su_mutex); /* for navigating configfs hierarchy */

	streaming = src->ci_parent->ci_parent;
	header = config_group_find_item(to_config_group(streaming), "header");
	if (!header || target->ci_parent != header)
		goto out;

	opts = to_f_uvc_opts(streaming->ci_parent);

	mutex_lock(&opts->lock);

	class_array = __uvcg_get_stream_class_arr(src, opts);
	if (!class_array || !*class_array)
		goto unlock;

	if (opts->refcnt)
		goto unlock;

	target_hdr = to_uvcg_streaming_header(target);
	--target_hdr->linked;
	kfree(**class_array);
	kfree(*class_array);
	*class_array = NULL;

unlock:
	mutex_unlock(&opts->lock);
out:
	config_item_put(header);
	mutex_unlock(su_mutex);
}