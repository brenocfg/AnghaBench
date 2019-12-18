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
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dcb; } ;
struct TYPE_3__ {void (* setpgtccfgtx ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct qede_dev* netdev_priv (struct net_device*) ; 
 void stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qede_dcbnl_setpgtccfgtx(struct net_device *netdev, int prio,
				    u8 pri_type, u8 pgid, u8 bw_pct, u8 up_map)
{
	struct qede_dev *edev = netdev_priv(netdev);

	return edev->ops->dcb->setpgtccfgtx(edev->cdev, prio, pri_type, pgid,
					    bw_pct, up_map);
}