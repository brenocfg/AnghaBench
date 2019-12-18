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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int num_hwfns; scalar_t__ smart_an; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct qede_dev {TYPE_2__ dev_info; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDE_PRI_FLAG_CMT ; 
 int /*<<< orphan*/  QEDE_PRI_FLAG_SMART_AN_SUPPORT ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 qede_get_priv_flags(struct net_device *dev)
{
	struct qede_dev *edev = netdev_priv(dev);
	u32 flags = 0;

	if (edev->dev_info.common.num_hwfns > 1)
		flags |= BIT(QEDE_PRI_FLAG_CMT);

	if (edev->dev_info.common.smart_an)
		flags |= BIT(QEDE_PRI_FLAG_SMART_AN_SUPPORT);

	return flags;
}