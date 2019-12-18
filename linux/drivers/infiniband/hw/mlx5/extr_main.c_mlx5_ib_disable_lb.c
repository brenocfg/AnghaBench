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
struct TYPE_2__ {int user_td; scalar_t__ qps; int enabled; int /*<<< orphan*/  mutex; } ;
struct mlx5_ib_dev {TYPE_1__ lb; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_nic_vport_update_local_lb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5_ib_disable_lb(struct mlx5_ib_dev *dev, bool td, bool qp)
{
	mutex_lock(&dev->lb.mutex);
	if (td)
		dev->lb.user_td--;
	if (qp)
		dev->lb.qps--;

	if (dev->lb.user_td == 1 &&
	    dev->lb.qps == 0) {
		if (dev->lb.enabled) {
			mlx5_nic_vport_update_local_lb(dev->mdev, false);
			dev->lb.enabled = false;
		}
	}

	mutex_unlock(&dev->lb.mutex);
}