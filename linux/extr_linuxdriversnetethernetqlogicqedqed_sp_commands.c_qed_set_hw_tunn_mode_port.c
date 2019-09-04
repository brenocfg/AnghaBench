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
struct qed_tunnel_info {TYPE_2__ geneve_port; TYPE_1__ vxlan_port; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_set_geneve_dest_port (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_set_hw_tunn_mode (struct qed_hwfn*,struct qed_ptt*,struct qed_tunnel_info*) ; 
 int /*<<< orphan*/  qed_set_vxlan_dest_port (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_set_hw_tunn_mode_port(struct qed_hwfn *p_hwfn,
				      struct qed_ptt *p_ptt,
				      struct qed_tunnel_info *p_tunn)
{
	if (p_tunn->vxlan_port.b_update_port)
		qed_set_vxlan_dest_port(p_hwfn, p_ptt,
					p_tunn->vxlan_port.port);

	if (p_tunn->geneve_port.b_update_port)
		qed_set_geneve_dest_port(p_hwfn, p_ptt,
					 p_tunn->geneve_port.port);

	qed_set_hw_tunn_mode(p_hwfn, p_ptt, p_tunn);
}