#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uvc_camera_terminal_descriptor {int bControlSize; int* bmControls; } ;
struct mutex {int dummy; } ;
struct f_uvc_opts {struct mutex lock; struct uvc_camera_terminal_descriptor uvc_camera_terminal; } ;
struct config_item {int dummy; } ;
struct TYPE_10__ {TYPE_4__* ci_parent; } ;
struct config_group {TYPE_5__ cg_item; TYPE_1__* cg_subsys; } ;
typedef  int ssize_t ;
struct TYPE_9__ {TYPE_3__* ci_parent; } ;
struct TYPE_8__ {TYPE_2__* ci_parent; } ;
struct TYPE_7__ {struct config_item* ci_parent; } ;
struct TYPE_6__ {struct mutex su_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 scalar_t__ sprintf (char*,char*,int) ; 
 struct config_group* to_config_group (struct config_item*) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t uvcg_default_camera_bm_controls_show(
	struct config_item *item, char *page)
{
	struct config_group *group = to_config_group(item);
	struct f_uvc_opts *opts;
	struct config_item *opts_item;
	struct mutex *su_mutex = &group->cg_subsys->su_mutex;
	struct uvc_camera_terminal_descriptor *cd;
	int result, i;
	char *pg = page;

	mutex_lock(su_mutex); /* for navigating configfs hierarchy */

	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent->
			ci_parent;
	opts = to_f_uvc_opts(opts_item);
	cd = &opts->uvc_camera_terminal;

	mutex_lock(&opts->lock);
	for (result = 0, i = 0; i < cd->bControlSize; ++i) {
		result += sprintf(pg, "%u\n", cd->bmControls[i]);
		pg = page + result;
	}
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);
	return result;
}