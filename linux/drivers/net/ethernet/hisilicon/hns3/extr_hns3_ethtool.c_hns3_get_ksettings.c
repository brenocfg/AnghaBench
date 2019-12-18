#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hnae3_handle {TYPE_1__* ae_algo; } ;
struct hnae3_ae_ops {int /*<<< orphan*/  (* get_mdix_mode ) (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_link_mode ) (struct hnae3_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_ksettings_an_result ) (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  eth_tp_mdix; int /*<<< orphan*/  eth_tp_mdix_ctrl; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct TYPE_5__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_3__ base; TYPE_2__ link_modes; } ;
struct TYPE_4__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct hnae3_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns3_get_ksettings(struct hnae3_handle *h,
			       struct ethtool_link_ksettings *cmd)
{
	const struct hnae3_ae_ops *ops = h->ae_algo->ops;

	/* 1.auto_neg & speed & duplex from cmd */
	if (ops->get_ksettings_an_result)
		ops->get_ksettings_an_result(h,
					     &cmd->base.autoneg,
					     &cmd->base.speed,
					     &cmd->base.duplex);

	/* 2.get link mode */
	if (ops->get_link_mode)
		ops->get_link_mode(h,
				   cmd->link_modes.supported,
				   cmd->link_modes.advertising);

	/* 3.mdix_ctrl&mdix get from phy reg */
	if (ops->get_mdix_mode)
		ops->get_mdix_mode(h, &cmd->base.eth_tp_mdix_ctrl,
				   &cmd->base.eth_tp_mdix);
}