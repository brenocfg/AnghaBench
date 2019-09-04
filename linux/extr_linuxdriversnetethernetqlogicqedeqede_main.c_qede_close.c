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
struct TYPE_3__ {int /*<<< orphan*/  (* update_drv_state ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QEDE_UNLOAD_NORMAL ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_unload (struct qede_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qede_close(struct net_device *ndev)
{
	struct qede_dev *edev = netdev_priv(ndev);

	qede_unload(edev, QEDE_UNLOAD_NORMAL, false);

	edev->ops->common->update_drv_state(edev->cdev, false);

	return 0;
}