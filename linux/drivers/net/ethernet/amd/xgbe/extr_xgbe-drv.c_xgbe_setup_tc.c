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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  (* config_tc ) (struct xgbe_prv_data*) ;} ;
struct TYPE_3__ {scalar_t__ tc_cnt; } ;
struct xgbe_prv_data {TYPE_2__ hw_if; scalar_t__ num_tcs; TYPE_1__ hw_feat; } ;
struct tc_mqprio_qopt {scalar_t__ num_tc; int /*<<< orphan*/  hw; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TC_MQPRIO_HW_OFFLOAD_TCS ; 
 int TC_SETUP_QDISC_MQPRIO ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_setup_tc(struct net_device *netdev, enum tc_setup_type type,
			 void *type_data)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct tc_mqprio_qopt *mqprio = type_data;
	u8 tc;

	if (type != TC_SETUP_QDISC_MQPRIO)
		return -EOPNOTSUPP;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	tc = mqprio->num_tc;

	if (tc > pdata->hw_feat.tc_cnt)
		return -EINVAL;

	pdata->num_tcs = tc;
	pdata->hw_if.config_tc(pdata);

	return 0;
}