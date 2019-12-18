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
struct inode {int dummy; } ;
struct ib_uverbs_file {int /*<<< orphan*/  ref; TYPE_1__* device; int /*<<< orphan*/  list; } ;
struct file {struct ib_uverbs_file* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  lists_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_REMOVE_CLOSE ; 
 int /*<<< orphan*/  ib_uverbs_release_file ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_destroy_ufile_hw (struct ib_uverbs_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ib_uverbs_close(struct inode *inode, struct file *filp)
{
	struct ib_uverbs_file *file = filp->private_data;

	uverbs_destroy_ufile_hw(file, RDMA_REMOVE_CLOSE);

	mutex_lock(&file->device->lists_mutex);
	list_del_init(&file->list);
	mutex_unlock(&file->device->lists_mutex);

	kref_put(&file->ref, ib_uverbs_release_file);

	return 0;
}