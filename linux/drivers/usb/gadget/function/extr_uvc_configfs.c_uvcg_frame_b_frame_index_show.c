#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int b_frame_index; } ;
struct TYPE_9__ {struct config_item* ci_parent; TYPE_2__* ci_group; } ;
struct uvcg_frame {TYPE_6__ frame; TYPE_3__ item; } ;
struct uvcg_format {int /*<<< orphan*/  linked; } ;
struct mutex {int dummy; } ;
struct f_uvc_opts {struct mutex lock; } ;
struct config_item {TYPE_5__* ci_parent; } ;
typedef  int ssize_t ;
struct TYPE_11__ {TYPE_4__* ci_parent; } ;
struct TYPE_10__ {struct config_item* ci_parent; } ;
struct TYPE_8__ {TYPE_1__* cg_subsys; } ;
struct TYPE_7__ {struct mutex su_mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int sprintf (char*,char*,int) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 
 struct uvcg_format* to_uvcg_format (struct config_item*) ; 
 struct uvcg_frame* to_uvcg_frame (struct config_item*) ; 

__attribute__((used)) static ssize_t uvcg_frame_b_frame_index_show(struct config_item *item,
					     char *page)
{
	struct uvcg_frame *f = to_uvcg_frame(item);
	struct uvcg_format *fmt;
	struct f_uvc_opts *opts;
	struct config_item *opts_item;
	struct config_item *fmt_item;
	struct mutex *su_mutex = &f->item.ci_group->cg_subsys->su_mutex;
	int result;

	mutex_lock(su_mutex); /* for navigating configfs hierarchy */

	fmt_item = f->item.ci_parent;
	fmt = to_uvcg_format(fmt_item);

	if (!fmt->linked) {
		result = -EBUSY;
		goto out;
	}

	opts_item = fmt_item->ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	result = sprintf(page, "%u\n", f->frame.b_frame_index);
	mutex_unlock(&opts->lock);

out:
	mutex_unlock(su_mutex);
	return result;
}