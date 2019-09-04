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
struct ethtool_regs {int /*<<< orphan*/  len; scalar_t__ version; } ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dbg_all_data ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void qede_get_regs(struct net_device *ndev,
			  struct ethtool_regs *regs, void *buffer)
{
	struct qede_dev *edev = netdev_priv(ndev);

	regs->version = 0;
	memset(buffer, 0, regs->len);

	if (edev->ops && edev->ops->common)
		edev->ops->common->dbg_all_data(edev->cdev, buffer);
}