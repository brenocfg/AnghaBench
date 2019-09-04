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
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_next_alias_guid_work {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ag_work_lock; } ;
struct TYPE_3__ {TYPE_2__ alias_guid; } ;
struct mlx4_ib_dev {TYPE_1__ sriov; } ;

/* Variables and functions */
 int ENOENT ; 
 int get_low_record_time_index (struct mlx4_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_required_record (struct mlx4_ib_dev*,int /*<<< orphan*/ ,struct mlx4_next_alias_guid_work*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int get_next_record_to_update(struct mlx4_ib_dev *dev, u8 port,
				     struct mlx4_next_alias_guid_work *rec)
{
	unsigned long flags;
	int record_index;
	int ret = 0;

	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags);
	record_index = get_low_record_time_index(dev, port, NULL);

	if (record_index < 0) {
		ret = -ENOENT;
		goto out;
	}

	set_required_record(dev, port, rec, record_index);
out:
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags);
	return ret;
}