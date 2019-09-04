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
struct msc_iter {struct msc* msc; } ;
struct msc {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct msc_iter* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  msc_iter_remove (struct msc_iter*,struct msc*) ; 

__attribute__((used)) static int intel_th_msc_release(struct inode *inode, struct file *file)
{
	struct msc_iter *iter = file->private_data;
	struct msc *msc = iter->msc;

	msc_iter_remove(iter, msc);

	return 0;
}