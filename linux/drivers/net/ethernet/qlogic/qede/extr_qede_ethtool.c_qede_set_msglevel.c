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
typedef  int /*<<< orphan*/  u32 ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_1__* ops; int /*<<< orphan*/  dp_module; int /*<<< orphan*/  dp_level; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_msglvl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__* common; } ;

/* Variables and functions */
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_config_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qede_set_msglevel(struct net_device *ndev, u32 level)
{
	struct qede_dev *edev = netdev_priv(ndev);
	u32 dp_module = 0;
	u8 dp_level = 0;

	qede_config_debug(level, &dp_module, &dp_level);

	edev->dp_level = dp_level;
	edev->dp_module = dp_module;
	edev->ops->common->update_msglvl(edev->cdev,
					 dp_module, dp_level);
}