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
struct fmc_device {int /*<<< orphan*/  owner; } ;
struct file {struct fmc_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_release(struct inode *ino, struct file *f)
{
	struct fmc_device *fmc = f->private_data;
	module_put(fmc->owner);
	return 0;
}