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
typedef  int /*<<< orphan*/  u16 ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct net_device {int dummy; } ;
struct dcb_peer_app_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dcb; } ;
struct TYPE_3__ {int (* peer_getappinfo ) (int /*<<< orphan*/ ,struct dcb_peer_app_info*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ,struct dcb_peer_app_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qede_dcbnl_peer_getappinfo(struct net_device *netdev,
				      struct dcb_peer_app_info *info,
				      u16 *count)
{
	struct qede_dev *edev = netdev_priv(netdev);

	return edev->ops->dcb->peer_getappinfo(edev->cdev, info, count);
}