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
struct pr_ops {int (* pr_register ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dm_target {int dummy; } ;
struct dm_pr {int /*<<< orphan*/  flags; int /*<<< orphan*/  new_key; int /*<<< orphan*/  old_key; } ;
struct dm_dev {TYPE_3__* bdev; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_6__ {TYPE_2__* bd_disk; } ;
struct TYPE_5__ {TYPE_1__* fops; } ;
struct TYPE_4__ {struct pr_ops* pr_ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dm_pr_register(struct dm_target *ti, struct dm_dev *dev,
			    sector_t start, sector_t len, void *data)
{
	struct dm_pr *pr = data;
	const struct pr_ops *ops = dev->bdev->bd_disk->fops->pr_ops;

	if (!ops || !ops->pr_register)
		return -EOPNOTSUPP;
	return ops->pr_register(dev->bdev, pr->old_key, pr->new_key, pr->flags);
}