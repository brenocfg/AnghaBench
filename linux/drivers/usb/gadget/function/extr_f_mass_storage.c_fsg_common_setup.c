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
struct fsg_common {int free_storage_on_release; int /*<<< orphan*/  luns; int /*<<< orphan*/  state; int /*<<< orphan*/  fsg_wait; int /*<<< orphan*/  io_wait; int /*<<< orphan*/  thread_notifier; int /*<<< orphan*/  lock; int /*<<< orphan*/  filesem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct fsg_common* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSG_STATE_TERMINATED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct fsg_common* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fsg_common *fsg_common_setup(struct fsg_common *common)
{
	if (!common) {
		common = kzalloc(sizeof(*common), GFP_KERNEL);
		if (!common)
			return ERR_PTR(-ENOMEM);
		common->free_storage_on_release = 1;
	} else {
		common->free_storage_on_release = 0;
	}
	init_rwsem(&common->filesem);
	spin_lock_init(&common->lock);
	init_completion(&common->thread_notifier);
	init_waitqueue_head(&common->io_wait);
	init_waitqueue_head(&common->fsg_wait);
	common->state = FSG_STATE_TERMINATED;
	memset(common->luns, 0, sizeof(common->luns));

	return common;
}