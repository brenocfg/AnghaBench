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
struct mutex {int dummy; } ;
struct f_uvc_opts {int control_interface; struct mutex lock; } ;
struct config_item {struct config_item* ci_parent; } ;
struct config_group {TYPE_1__* cg_subsys; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct mutex su_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 scalar_t__ sprintf (char*,char*,int) ; 
 struct config_group* to_config_group (struct config_item*) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t uvcg_default_control_b_interface_number_show(
	struct config_item *item, char *page)
{
	struct config_group *group = to_config_group(item);
	struct mutex *su_mutex = &group->cg_subsys->su_mutex;
	struct config_item *opts_item;
	struct f_uvc_opts *opts;
	int result = 0;

	mutex_lock(su_mutex); /* for navigating configfs hierarchy */

	opts_item = item->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	result += sprintf(page, "%u\n", opts->control_interface);
	mutex_unlock(&opts->lock);

	mutex_unlock(su_mutex);

	return result;
}