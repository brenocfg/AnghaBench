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
struct qed_hwfn {TYPE_1__* p_dcbx_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  peer_port_id; int /*<<< orphan*/  peer_chassis_id; } ;
struct qed_dcbx_get {TYPE_2__ lldp_remote; } ;
struct lldp_status_params_s {int /*<<< orphan*/  peer_port_id; int /*<<< orphan*/  peer_chassis_id; } ;
struct TYPE_3__ {struct lldp_status_params_s* lldp_remote; } ;

/* Variables and functions */
 size_t LLDP_NEAREST_BRIDGE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qed_dcbx_get_remote_lldp_params(struct qed_hwfn *p_hwfn,
				struct qed_dcbx_get *params)
{
	struct lldp_status_params_s *p_remote;

	p_remote = &p_hwfn->p_dcbx_info->lldp_remote[LLDP_NEAREST_BRIDGE];

	memcpy(params->lldp_remote.peer_chassis_id, p_remote->peer_chassis_id,
	       sizeof(p_remote->peer_chassis_id));
	memcpy(params->lldp_remote.peer_port_id, p_remote->peer_port_id,
	       sizeof(p_remote->peer_port_id));
}