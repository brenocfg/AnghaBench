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
struct sync_file {int /*<<< orphan*/  fence; int /*<<< orphan*/  cb; int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct file {struct sync_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_ENABLED ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_remove_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sync_file*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sync_file_release(struct inode *inode, struct file *file)
{
	struct sync_file *sync_file = file->private_data;

	if (test_bit(POLL_ENABLED, &sync_file->flags))
		dma_fence_remove_callback(sync_file->fence, &sync_file->cb);
	dma_fence_put(sync_file->fence);
	kfree(sync_file);

	return 0;
}