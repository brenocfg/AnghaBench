#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct aq_nic_s {int /*<<< orphan*/  fwreq_mutex; int /*<<< orphan*/  aq_hw; TYPE_1__* aq_fw_ops; } ;
struct TYPE_2__ {int (* renegotiate ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aq_ethtool_nway_reset(struct net_device *ndev)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	int err = 0;

	if (unlikely(!aq_nic->aq_fw_ops->renegotiate))
		return -EOPNOTSUPP;

	if (netif_running(ndev)) {
		mutex_lock(&aq_nic->fwreq_mutex);
		err = aq_nic->aq_fw_ops->renegotiate(aq_nic->aq_hw);
		mutex_unlock(&aq_nic->fwreq_mutex);
	}

	return err;
}