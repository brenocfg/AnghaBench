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
struct net_device {int dummy; } ;
struct hns_nic_priv {TYPE_2__* ae_handle; } ;
struct hnae_ae_ops {int /*<<< orphan*/  (* get_regs ) (TYPE_2__*,void*) ;} ;
struct ethtool_regs {int /*<<< orphan*/  version; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {struct hnae_ae_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_CHIP_VERSION ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*) ; 

__attribute__((used)) static void hns_get_regs(struct net_device *net_dev, struct ethtool_regs *cmd,
			 void *data)
{
	struct hns_nic_priv *priv = netdev_priv(net_dev);
	struct hnae_ae_ops *ops;

	ops = priv->ae_handle->dev->ops;

	cmd->version = HNS_CHIP_VERSION;
	if (!ops->get_regs) {
		netdev_err(net_dev, "ops->get_regs is null!\n");
		return;
	}
	ops->get_regs(priv->ae_handle, data);
}