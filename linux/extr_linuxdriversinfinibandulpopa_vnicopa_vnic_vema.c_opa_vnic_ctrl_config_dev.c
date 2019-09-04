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
struct opa_vnic_ctrl_port {int num_ports; int /*<<< orphan*/  ibdev; } ;
struct ib_port_modify {void* clr_port_cap_mask; void* set_port_cap_mask; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PORT_OPA_MASK_CHG ; 
 void* OPA_CAP_MASK3_IsEthOnFabricSupported ; 
 int /*<<< orphan*/  ib_modify_port (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ib_port_modify*) ; 

__attribute__((used)) static void opa_vnic_ctrl_config_dev(struct opa_vnic_ctrl_port *cport, bool en)
{
	struct ib_port_modify pm = { 0 };
	int i;

	if (en)
		pm.set_port_cap_mask = OPA_CAP_MASK3_IsEthOnFabricSupported;
	else
		pm.clr_port_cap_mask = OPA_CAP_MASK3_IsEthOnFabricSupported;

	for (i = 1; i <= cport->num_ports; i++)
		ib_modify_port(cport->ibdev, i, IB_PORT_OPA_MASK_CHG, &pm);
}