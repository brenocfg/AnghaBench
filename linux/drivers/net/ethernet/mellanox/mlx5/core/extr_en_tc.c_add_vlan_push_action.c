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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int dummy; } ;
struct mlx5_esw_flow_attr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  prio; int /*<<< orphan*/  proto; int /*<<< orphan*/  vid; } ;
struct flow_action_entry {TYPE_1__ vlan; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_ACTION_VLAN_PUSH ; 
 struct net_device* dev_get_by_index_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_iflink (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int parse_tc_vlan_action (struct mlx5e_priv*,struct flow_action_entry*,struct mlx5_esw_flow_attr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (struct net_device*) ; 
 int /*<<< orphan*/  vlan_dev_vlan_proto (struct net_device*) ; 

__attribute__((used)) static int add_vlan_push_action(struct mlx5e_priv *priv,
				struct mlx5_esw_flow_attr *attr,
				struct net_device **out_dev,
				u32 *action)
{
	struct net_device *vlan_dev = *out_dev;
	struct flow_action_entry vlan_act = {
		.id = FLOW_ACTION_VLAN_PUSH,
		.vlan.vid = vlan_dev_vlan_id(vlan_dev),
		.vlan.proto = vlan_dev_vlan_proto(vlan_dev),
		.vlan.prio = 0,
	};
	int err;

	err = parse_tc_vlan_action(priv, &vlan_act, attr, action);
	if (err)
		return err;

	*out_dev = dev_get_by_index_rcu(dev_net(vlan_dev),
					dev_get_iflink(vlan_dev));
	if (is_vlan_dev(*out_dev))
		err = add_vlan_push_action(priv, attr, out_dev, action);

	return err;
}