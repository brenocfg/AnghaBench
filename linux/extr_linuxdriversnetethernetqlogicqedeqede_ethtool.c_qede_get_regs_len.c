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
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int (* dbg_all_data_size ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qede_get_regs_len(struct net_device *ndev)
{
	struct qede_dev *edev = netdev_priv(ndev);

	if (edev->ops && edev->ops->common)
		return edev->ops->common->dbg_all_data_size(edev->cdev);
	else
		return -EINVAL;
}