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
struct tc_mqprio_qopt {scalar_t__ num_tc; int /*<<< orphan*/  hw; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ MLX4_EN_NUM_UP_HIGH ; 
 int /*<<< orphan*/  TC_MQPRIO_HW_OFFLOAD_TCS ; 
 int TC_SETUP_QDISC_MQPRIO ; 
 int mlx4_en_alloc_tx_queue_per_tc (struct net_device*,scalar_t__) ; 

__attribute__((used)) static int __mlx4_en_setup_tc(struct net_device *dev, enum tc_setup_type type,
			      void *type_data)
{
	struct tc_mqprio_qopt *mqprio = type_data;

	if (type != TC_SETUP_QDISC_MQPRIO)
		return -EOPNOTSUPP;

	if (mqprio->num_tc && mqprio->num_tc != MLX4_EN_NUM_UP_HIGH)
		return -EINVAL;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

	return mlx4_en_alloc_tx_queue_per_tc(dev, mqprio->num_tc);
}