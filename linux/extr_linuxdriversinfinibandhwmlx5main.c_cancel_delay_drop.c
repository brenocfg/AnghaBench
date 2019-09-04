#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  delay_drop_work; } ;
struct TYPE_4__ {int raw_packet_caps; } ;
struct TYPE_5__ {TYPE_1__ attrs; } ;
struct mlx5_ib_dev {TYPE_3__ delay_drop; TYPE_2__ ib_dev; } ;

/* Variables and functions */
 int IB_RAW_PACKET_CAP_DELAY_DROP ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delay_drop_debugfs_cleanup (struct mlx5_ib_dev*) ; 

__attribute__((used)) static void cancel_delay_drop(struct mlx5_ib_dev *dev)
{
	if (!(dev->ib_dev.attrs.raw_packet_caps & IB_RAW_PACKET_CAP_DELAY_DROP))
		return;

	cancel_work_sync(&dev->delay_drop.delay_drop_work);
	delay_drop_debugfs_cleanup(dev);
}