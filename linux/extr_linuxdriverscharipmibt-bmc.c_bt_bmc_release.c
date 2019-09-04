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
struct file {int dummy; } ;
struct bt_bmc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct bt_bmc* file_bt_bmc (struct file*) ; 
 int /*<<< orphan*/  open_count ; 
 int /*<<< orphan*/  set_b_busy (struct bt_bmc*) ; 

__attribute__((used)) static int bt_bmc_release(struct inode *inode, struct file *file)
{
	struct bt_bmc *bt_bmc = file_bt_bmc(file);

	atomic_dec(&open_count);
	set_b_busy(bt_bmc);
	return 0;
}