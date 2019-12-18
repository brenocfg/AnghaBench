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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ num_tc; scalar_t__ hw; scalar_t__* prio_tc_map; } ;
struct tc_mqprio_qopt_offload {scalar_t__ mode; TYPE_1__ qopt; } ;
struct net_device {int dummy; } ;
struct hnae3_knic_private_info {TYPE_2__* dcb_ops; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;
struct TYPE_4__ {int (* setup_tc ) (struct hnae3_handle*,scalar_t__,scalar_t__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ HNAE3_MAX_TC ; 
 scalar_t__ TC_MQPRIO_HW_OFFLOAD_TCS ; 
 scalar_t__ TC_MQPRIO_MODE_CHANNEL ; 
 int /*<<< orphan*/  drv ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct hnae3_handle*,int /*<<< orphan*/ ,struct net_device*,char*,scalar_t__) ; 
 int stub1 (struct hnae3_handle*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int hns3_setup_tc(struct net_device *netdev, void *type_data)
{
	struct tc_mqprio_qopt_offload *mqprio_qopt = type_data;
	u8 *prio_tc = mqprio_qopt->qopt.prio_tc_map;
	struct hnae3_knic_private_info *kinfo;
	u8 tc = mqprio_qopt->qopt.num_tc;
	u16 mode = mqprio_qopt->mode;
	u8 hw = mqprio_qopt->qopt.hw;
	struct hnae3_handle *h;

	if (!((hw == TC_MQPRIO_HW_OFFLOAD_TCS &&
	       mode == TC_MQPRIO_MODE_CHANNEL) || (!hw && tc == 0)))
		return -EOPNOTSUPP;

	if (tc > HNAE3_MAX_TC)
		return -EINVAL;

	if (!netdev)
		return -EINVAL;

	h = hns3_get_handle(netdev);
	kinfo = &h->kinfo;

	netif_dbg(h, drv, netdev, "setup tc: num_tc=%u\n", tc);

	return (kinfo->dcb_ops && kinfo->dcb_ops->setup_tc) ?
		kinfo->dcb_ops->setup_tc(h, tc, prio_tc) : -EOPNOTSUPP;
}