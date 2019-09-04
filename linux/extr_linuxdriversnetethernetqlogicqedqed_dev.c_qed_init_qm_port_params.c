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
typedef  size_t u8 ;
struct TYPE_3__ {struct init_qm_port_params* qm_port_params; } ;
struct qed_hwfn {TYPE_1__ qm_info; TYPE_2__* cdev; } ;
struct init_qm_port_params {int active; size_t active_phys_tcs; size_t num_pbf_cmd_lines; size_t num_btb_blocks; } ;
struct TYPE_4__ {size_t num_ports_in_engine; } ;

/* Variables and functions */
 size_t ACTIVE_TCS_BMAP ; 
 size_t ACTIVE_TCS_BMAP_4PORT_K2 ; 
 size_t BTB_MAX_BLOCKS ; 
 size_t MAX_NUM_PORTS_K2 ; 
 size_t PBF_MAX_CMD_LINES ; 

__attribute__((used)) static void qed_init_qm_port_params(struct qed_hwfn *p_hwfn)
{
	/* Initialize qm port parameters */
	u8 i, active_phys_tcs, num_ports = p_hwfn->cdev->num_ports_in_engine;

	/* indicate how ooo and high pri traffic is dealt with */
	active_phys_tcs = num_ports == MAX_NUM_PORTS_K2 ?
			  ACTIVE_TCS_BMAP_4PORT_K2 :
			  ACTIVE_TCS_BMAP;

	for (i = 0; i < num_ports; i++) {
		struct init_qm_port_params *p_qm_port =
		    &p_hwfn->qm_info.qm_port_params[i];

		p_qm_port->active = 1;
		p_qm_port->active_phys_tcs = active_phys_tcs;
		p_qm_port->num_pbf_cmd_lines = PBF_MAX_CMD_LINES / num_ports;
		p_qm_port->num_btb_blocks = BTB_MAX_BLOCKS / num_ports;
	}
}