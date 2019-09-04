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
struct TYPE_2__ {int activate; int /*<<< orphan*/  rqs_cnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  timeout; } ;
struct mlx5_ib_dev {TYPE_1__ delay_drop; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int mlx5_core_set_delay_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_delay_drop(struct mlx5_ib_dev *dev)
{
	int err = 0;

	mutex_lock(&dev->delay_drop.lock);
	if (dev->delay_drop.activate)
		goto out;

	err = mlx5_core_set_delay_drop(dev->mdev, dev->delay_drop.timeout);
	if (err)
		goto out;

	dev->delay_drop.activate = true;
out:
	mutex_unlock(&dev->delay_drop.lock);

	if (!err)
		atomic_inc(&dev->delay_drop.rqs_cnt);
	return err;
}