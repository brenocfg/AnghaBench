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
struct TYPE_4__ {int /*<<< orphan*/  port; scalar_t__ b_update_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; scalar_t__ b_update_port; } ;
struct qed_tunnel_info {TYPE_2__ vxlan_port; TYPE_1__ geneve_port; } ;

/* Variables and functions */

__attribute__((used)) static void qed_set_tunn_ports(struct qed_tunnel_info *p_tun,
			       struct qed_tunnel_info *p_src)
{
	p_tun->geneve_port.b_update_port = p_src->geneve_port.b_update_port;
	p_tun->vxlan_port.b_update_port = p_src->vxlan_port.b_update_port;

	if (p_src->geneve_port.b_update_port)
		p_tun->geneve_port.port = p_src->geneve_port.port;

	if (p_src->vxlan_port.b_update_port)
		p_tun->vxlan_port.port = p_src->vxlan_port.port;
}