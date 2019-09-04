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
struct inode {int dummy; } ;
struct ib_uverbs_file {int is_closed; int /*<<< orphan*/  ref; TYPE_1__* async_file; TYPE_2__* device; int /*<<< orphan*/  list; } ;
struct file {struct ib_uverbs_file* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  lists_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_REMOVE_CLOSE ; 
 int /*<<< orphan*/  ib_uverbs_release_async_event_file ; 
 int /*<<< orphan*/  ib_uverbs_release_file ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_destroy_ufile_hw (struct ib_uverbs_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ib_uverbs_close(struct inode *inode, struct file *filp)
{
	struct ib_uverbs_file *file = filp->private_data;

	uverbs_destroy_ufile_hw(file, RDMA_REMOVE_CLOSE);

	mutex_lock(&file->device->lists_mutex);
	if (!file->is_closed) {
		list_del(&file->list);
		file->is_closed = 1;
	}
	mutex_unlock(&file->device->lists_mutex);

	if (file->async_file)
		kref_put(&file->async_file->ref,
			 ib_uverbs_release_async_event_file);

	kref_put(&file->ref, ib_uverbs_release_file);

	return 0;
}