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
struct inode {int dummy; } ;
struct file {struct cs_char* private_data; } ;
struct cs_char {int /*<<< orphan*/  lock; scalar_t__ opened; int /*<<< orphan*/  dataind_queue; int /*<<< orphan*/  chardev_queue; int /*<<< orphan*/  mmap_base; int /*<<< orphan*/ * hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_free_char_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_hsi_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs_char_release(struct inode *unused, struct file *file)
{
	struct cs_char *csdata = file->private_data;

	cs_hsi_stop(csdata->hi);
	spin_lock_bh(&csdata->lock);
	csdata->hi = NULL;
	free_page(csdata->mmap_base);
	cs_free_char_queue(&csdata->chardev_queue);
	cs_free_char_queue(&csdata->dataind_queue);
	csdata->opened = 0;
	spin_unlock_bh(&csdata->lock);

	return 0;
}