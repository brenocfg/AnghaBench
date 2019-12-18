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
struct fsg_opts {int /*<<< orphan*/  lock; TYPE_2__* common; scalar_t__ refcnt; } ;
struct fsg_lun_opts {size_t lun_id; int /*<<< orphan*/  lun; } ;
struct config_item {int dummy; } ;
struct TYPE_6__ {TYPE_1__* ci_parent; } ;
struct config_group {TYPE_3__ cg_item; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** luns; } ;
struct TYPE_4__ {struct config_item* ci_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  fsg_common_remove_lun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fsg_lun_opts* to_fsg_lun_opts (struct config_item*) ; 
 struct fsg_opts* to_fsg_opts (TYPE_3__*) ; 
 int /*<<< orphan*/  unregister_gadget_item (struct config_item*) ; 

__attribute__((used)) static void fsg_lun_drop(struct config_group *group, struct config_item *item)
{
	struct fsg_lun_opts *lun_opts;
	struct fsg_opts *fsg_opts;

	lun_opts = to_fsg_lun_opts(item);
	fsg_opts = to_fsg_opts(&group->cg_item);

	mutex_lock(&fsg_opts->lock);
	if (fsg_opts->refcnt) {
		struct config_item *gadget;

		gadget = group->cg_item.ci_parent->ci_parent;
		unregister_gadget_item(gadget);
	}

	fsg_common_remove_lun(lun_opts->lun);
	fsg_opts->common->luns[lun_opts->lun_id] = NULL;
	lun_opts->lun_id = 0;
	mutex_unlock(&fsg_opts->lock);

	config_item_put(item);
}