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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct tb_xdomain {int /*<<< orphan*/  receive_path; int /*<<< orphan*/  receive_ring; int /*<<< orphan*/  transmit_path; int /*<<< orphan*/  transmit_ring; int /*<<< orphan*/  route; TYPE_1__ dev; } ;
struct tb_tunnel {int /*<<< orphan*/  list; } ;
struct tb_switch {int dummy; } ;
struct tb_port {int dummy; } ;
struct tb_cm {int /*<<< orphan*/  tunnel_list; } ;
struct tb {int /*<<< orphan*/  lock; int /*<<< orphan*/  root_switch; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TB_TYPE_NHI ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tb_port* tb_find_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tb_port* tb_port_at (int /*<<< orphan*/ ,struct tb_switch*) ; 
 int /*<<< orphan*/  tb_port_info (struct tb_port*,char*) ; 
 struct tb_cm* tb_priv (struct tb*) ; 
 struct tb_switch* tb_to_switch (int /*<<< orphan*/ ) ; 
 scalar_t__ tb_tunnel_activate (struct tb_tunnel*) ; 
 struct tb_tunnel* tb_tunnel_alloc_dma (struct tb*,struct tb_port*,struct tb_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_tunnel_free (struct tb_tunnel*) ; 

__attribute__((used)) static int tb_approve_xdomain_paths(struct tb *tb, struct tb_xdomain *xd)
{
	struct tb_cm *tcm = tb_priv(tb);
	struct tb_port *nhi_port, *dst_port;
	struct tb_tunnel *tunnel;
	struct tb_switch *sw;

	sw = tb_to_switch(xd->dev.parent);
	dst_port = tb_port_at(xd->route, sw);
	nhi_port = tb_find_port(tb->root_switch, TB_TYPE_NHI);

	mutex_lock(&tb->lock);
	tunnel = tb_tunnel_alloc_dma(tb, nhi_port, dst_port, xd->transmit_ring,
				     xd->transmit_path, xd->receive_ring,
				     xd->receive_path);
	if (!tunnel) {
		mutex_unlock(&tb->lock);
		return -ENOMEM;
	}

	if (tb_tunnel_activate(tunnel)) {
		tb_port_info(nhi_port,
			     "DMA tunnel activation failed, aborting\n");
		tb_tunnel_free(tunnel);
		mutex_unlock(&tb->lock);
		return -EIO;
	}

	list_add_tail(&tunnel->list, &tcm->tunnel_list);
	mutex_unlock(&tb->lock);
	return 0;
}