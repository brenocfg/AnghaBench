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
struct uvc_descriptor_header {int dummy; } ;
struct mutex {int dummy; } ;
struct f_uvc_opts {struct mutex lock; int /*<<< orphan*/  uvc_color_matching; scalar_t__ refcnt; } ;
struct config_item {struct config_item* ci_parent; TYPE_2__* ci_group; } ;
struct TYPE_4__ {TYPE_1__* cg_subsys; } ;
struct TYPE_3__ {struct mutex su_mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __uvcg_cnt_strm ; 
 int /*<<< orphan*/  __uvcg_fill_strm ; 
 struct uvc_descriptor_header*** __uvcg_get_stream_class_arr (struct config_item*,struct f_uvc_opts*) ; 
 int __uvcg_iter_strm_cls (struct uvcg_streaming_header*,...) ; 
 struct config_item* config_group_find_item (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 struct uvc_descriptor_header** kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 
 struct uvcg_streaming_header* to_uvcg_streaming_header (struct config_item*) ; 

__attribute__((used)) static int uvcg_streaming_class_allow_link(struct config_item *src,
					   struct config_item *target)
{
	struct config_item *streaming, *header;
	struct f_uvc_opts *opts;
	struct mutex *su_mutex = &src->ci_group->cg_subsys->su_mutex;
	struct uvc_descriptor_header ***class_array, **cl_arr;
	struct uvcg_streaming_header *target_hdr;
	void *data, *data_save;
	size_t size = 0, count = 0;
	int ret = -EINVAL;

	mutex_lock(su_mutex); /* for navigating configfs hierarchy */

	streaming = src->ci_parent->ci_parent;
	header = config_group_find_item(to_config_group(streaming), "header");
	if (!header || target->ci_parent != header)
		goto out;

	opts = to_f_uvc_opts(streaming->ci_parent);

	mutex_lock(&opts->lock);

	class_array = __uvcg_get_stream_class_arr(src, opts);
	if (!class_array || *class_array || opts->refcnt) {
		ret = -EBUSY;
		goto unlock;
	}

	target_hdr = to_uvcg_streaming_header(target);
	ret = __uvcg_iter_strm_cls(target_hdr, &size, &count, __uvcg_cnt_strm);
	if (ret)
		goto unlock;

	count += 2; /* color_matching, NULL */
	*class_array = kcalloc(count, sizeof(void *), GFP_KERNEL);
	if (!*class_array) {
		ret = -ENOMEM;
		goto unlock;
	}

	data = data_save = kzalloc(size, GFP_KERNEL);
	if (!data) {
		kfree(*class_array);
		*class_array = NULL;
		ret = -ENOMEM;
		goto unlock;
	}
	cl_arr = *class_array;
	ret = __uvcg_iter_strm_cls(target_hdr, &data, &cl_arr,
				   __uvcg_fill_strm);
	if (ret) {
		kfree(*class_array);
		*class_array = NULL;
		/*
		 * __uvcg_fill_strm() called from __uvcg_iter_stream_cls()
		 * might have advanced the "data", so use a backup copy
		 */
		kfree(data_save);
		goto unlock;
	}
	*cl_arr = (struct uvc_descriptor_header *)&opts->uvc_color_matching;

	++target_hdr->linked;
	ret = 0;

unlock:
	mutex_unlock(&opts->lock);
out:
	config_item_put(header);
	mutex_unlock(su_mutex);
	return ret;
}