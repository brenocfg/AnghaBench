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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct psample_group {int dummy; } ;
struct mlxsw_sp_port {TYPE_3__* sample; TYPE_2__* dev; } ;
struct mlxsw_sp {TYPE_1__* bus_info; struct mlxsw_sp_port** ports; } ;
struct TYPE_6__ {int /*<<< orphan*/  rate; int /*<<< orphan*/  psample_group; int /*<<< orphan*/  trunc_size; scalar_t__ truncate; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  psample_sample_packet (struct psample_group*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct psample_group* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mlxsw_sp_rx_listener_sample_func(struct sk_buff *skb, u8 local_port,
					     void *priv)
{
	struct mlxsw_sp *mlxsw_sp = priv;
	struct mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp->ports[local_port];
	struct psample_group *psample_group;
	u32 size;

	if (unlikely(!mlxsw_sp_port)) {
		dev_warn_ratelimited(mlxsw_sp->bus_info->dev, "Port %d: sample skb received for non-existent port\n",
				     local_port);
		goto out;
	}
	if (unlikely(!mlxsw_sp_port->sample)) {
		dev_warn_ratelimited(mlxsw_sp->bus_info->dev, "Port %d: sample skb received on unsupported port\n",
				     local_port);
		goto out;
	}

	size = mlxsw_sp_port->sample->truncate ?
		  mlxsw_sp_port->sample->trunc_size : skb->len;

	rcu_read_lock();
	psample_group = rcu_dereference(mlxsw_sp_port->sample->psample_group);
	if (!psample_group)
		goto out_unlock;
	psample_sample_packet(psample_group, skb, size,
			      mlxsw_sp_port->dev->ifindex, 0,
			      mlxsw_sp_port->sample->rate);
out_unlock:
	rcu_read_unlock();
out:
	consume_skb(skb);
}