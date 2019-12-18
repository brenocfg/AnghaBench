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
struct opa_vnic_vema_port {int /*<<< orphan*/  class_port_info; } ;
struct opa_vnic_vema_mad {scalar_t__ data; } ;
struct opa_class_port_info {int /*<<< orphan*/  cap_mask2_resp_time; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  class_version; int /*<<< orphan*/  base_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPA_EMA_CLASS_VERSION ; 
 int /*<<< orphan*/  OPA_MGMT_BASE_VERSION ; 
 int OPA_VNIC_CLASS_CAP_TRAP ; 
 int OPA_VNIC_MAX_NUM_VPORT ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (struct opa_class_port_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vema_get_class_port_info(struct opa_vnic_vema_port *port,
				     struct opa_vnic_vema_mad *recvd_mad,
				     struct opa_vnic_vema_mad *rsp_mad)
{
	struct opa_class_port_info *port_info;

	port_info = (struct opa_class_port_info *)rsp_mad->data;
	memcpy(port_info, &port->class_port_info, sizeof(*port_info));
	port_info->base_version = OPA_MGMT_BASE_VERSION,
	port_info->class_version = OPA_EMA_CLASS_VERSION;

	/*
	 * Set capability mask bit indicating agent generates traps,
	 * and set the maximum number of VNIC ports supported.
	 */
	port_info->cap_mask = cpu_to_be16((OPA_VNIC_CLASS_CAP_TRAP |
					   (OPA_VNIC_MAX_NUM_VPORT << 8)));

	/*
	 * Since a get routine is always sent by the EM first we
	 * set the expected response time to
	 * 4.096 usec * 2^18 == 1.0737 sec here.
	 */
	port_info->cap_mask2_resp_time = cpu_to_be32(18);
}