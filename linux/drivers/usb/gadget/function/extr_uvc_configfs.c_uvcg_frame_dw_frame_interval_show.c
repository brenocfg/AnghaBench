#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int b_frame_interval_type; } ;
struct TYPE_13__ {TYPE_5__* ci_parent; TYPE_2__* ci_group; } ;
struct uvcg_frame {int* dw_frame_interval; TYPE_7__ frame; TYPE_6__ item; } ;
struct mutex {int dummy; } ;
struct f_uvc_opts {struct mutex lock; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_12__ {TYPE_4__* ci_parent; } ;
struct TYPE_11__ {TYPE_3__* ci_parent; } ;
struct TYPE_10__ {struct config_item* ci_parent; } ;
struct TYPE_9__ {TYPE_1__* cg_subsys; } ;
struct TYPE_8__ {struct mutex su_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 scalar_t__ sprintf (char*,char*,int) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 
 struct uvcg_frame* to_uvcg_frame (struct config_item*) ; 

__attribute__((used)) static ssize_t uvcg_frame_dw_frame_interval_show(struct config_item *item,
						 char *page)
{
	struct uvcg_frame *frm = to_uvcg_frame(item);
	struct f_uvc_opts *opts;
	struct config_item *opts_item;
	struct mutex *su_mutex = &frm->item.ci_group->cg_subsys->su_mutex;
	int result, i;
	char *pg = page;

	mutex_lock(su_mutex); /* for navigating configfs hierarchy */

	opts_item = frm->item.ci_parent->ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	for (result = 0, i = 0; i < frm->frame.b_frame_interval_type; ++i) {
		result += sprintf(pg, "%u\n", frm->dw_frame_interval[i]);
		pg = page + result;
	}
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);
	return result;
}