#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uvcg_format {int /*<<< orphan*/  num_frames; } ;
struct f_uvc_opts {int /*<<< orphan*/  lock; } ;
struct config_item {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ci_parent; } ;
struct config_group {TYPE_3__ cg_item; } ;
struct TYPE_5__ {TYPE_1__* ci_parent; } ;
struct TYPE_4__ {struct config_item* ci_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 
 struct uvcg_format* to_uvcg_format (TYPE_3__*) ; 

__attribute__((used)) static void uvcg_frame_drop(struct config_group *group, struct config_item *item)
{
	struct uvcg_format *fmt;
	struct f_uvc_opts *opts;
	struct config_item *opts_item;

	opts_item = group->cg_item.ci_parent->ci_parent->ci_parent;
	opts = to_f_uvc_opts(opts_item);

	mutex_lock(&opts->lock);
	fmt = to_uvcg_format(&group->cg_item);
	--fmt->num_frames;
	mutex_unlock(&opts->lock);

	config_item_put(item);
}