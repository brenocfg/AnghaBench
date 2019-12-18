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
struct TYPE_3__ {void* fcoe_wwn_node_name_lo; void* fcoe_wwn_node_name_hi; void* fcoe_wwn_port_name_lo; void* fcoe_wwn_port_name_hi; } ;
struct bnx2x {TYPE_1__ cnic_eth_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  fcoe_wwn_node_name_lower; int /*<<< orphan*/  fcoe_wwn_node_name_upper; int /*<<< orphan*/  fcoe_wwn_port_name_lower; int /*<<< orphan*/  fcoe_wwn_port_name_upper; } ;

/* Variables and functions */
 void* MF_CFG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 TYPE_2__* func_ext_config ; 

__attribute__((used)) static void bnx2x_get_ext_wwn_info(struct bnx2x *bp, int func)
{
	/* Port info */
	bp->cnic_eth_dev.fcoe_wwn_port_name_hi =
		MF_CFG_RD(bp, func_ext_config[func].fcoe_wwn_port_name_upper);
	bp->cnic_eth_dev.fcoe_wwn_port_name_lo =
		MF_CFG_RD(bp, func_ext_config[func].fcoe_wwn_port_name_lower);

	/* Node info */
	bp->cnic_eth_dev.fcoe_wwn_node_name_hi =
		MF_CFG_RD(bp, func_ext_config[func].fcoe_wwn_node_name_upper);
	bp->cnic_eth_dev.fcoe_wwn_node_name_lo =
		MF_CFG_RD(bp, func_ext_config[func].fcoe_wwn_node_name_lower);
}