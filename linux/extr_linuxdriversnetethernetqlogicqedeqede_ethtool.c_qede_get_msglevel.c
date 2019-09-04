#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct qede_dev {int dp_module; scalar_t__ dp_level; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int QED_LOG_LEVEL_SHIFT ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 qede_get_msglevel(struct net_device *ndev)
{
	struct qede_dev *edev = netdev_priv(ndev);

	return ((u32)edev->dp_level << QED_LOG_LEVEL_SHIFT) | edev->dp_module;
}