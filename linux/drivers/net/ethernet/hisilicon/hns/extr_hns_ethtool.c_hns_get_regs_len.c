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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct hns_nic_priv {TYPE_2__* ae_handle; } ;
struct hnae_ae_ops {int (* get_regs_len ) (TYPE_2__*) ;} ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {struct hnae_ae_ops* ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int hns_get_regs_len(struct net_device *net_dev)
{
	u32 reg_num;
	struct hns_nic_priv *priv = netdev_priv(net_dev);
	struct hnae_ae_ops *ops;

	ops = priv->ae_handle->dev->ops;
	if (!ops->get_regs_len) {
		netdev_err(net_dev, "ops->get_regs_len is null!\n");
		return -EOPNOTSUPP;
	}

	reg_num = ops->get_regs_len(priv->ae_handle);
	if (reg_num > 0)
		return reg_num * sizeof(u32);
	else
		return reg_num;	/* error code */
}