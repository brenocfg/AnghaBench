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
struct udp_tunnel_info {scalar_t__ type; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vxlan_port; } ;
struct be_cmd_work {int /*<<< orphan*/  work; TYPE_1__ info; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 scalar_t__ UDP_TUNNEL_TYPE_VXLAN ; 
 struct be_cmd_work* be_alloc_work (struct be_adapter*,void (*) (struct work_struct*)) ; 
 scalar_t__ be_is_mc (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wq ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void be_cfg_vxlan_port(struct net_device *netdev,
			      struct udp_tunnel_info *ti,
			      void (*func)(struct work_struct *))
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct be_cmd_work *cmd_work;

	if (ti->type != UDP_TUNNEL_TYPE_VXLAN)
		return;

	if (lancer_chip(adapter) || BEx_chip(adapter) || be_is_mc(adapter))
		return;

	cmd_work = be_alloc_work(adapter, func);
	if (cmd_work) {
		cmd_work->info.vxlan_port = ti->port;
		queue_work(be_wq, &cmd_work->work);
	}
}