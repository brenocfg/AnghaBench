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
struct TYPE_3__ {TYPE_2__* dbg; } ;
struct mlx5_ib_dev {TYPE_1__ delay_drop; } ;
struct TYPE_4__ {int /*<<< orphan*/  dir_debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void delay_drop_debugfs_cleanup(struct mlx5_ib_dev *dev)
{
	if (!dev->delay_drop.dbg)
		return;
	debugfs_remove_recursive(dev->delay_drop.dbg->dir_debugfs);
	kfree(dev->delay_drop.dbg);
	dev->delay_drop.dbg = NULL;
}