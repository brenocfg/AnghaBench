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
struct opa_vnic_vema_mad {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vema_get_class_port_info (struct opa_vnic_vema_port*,struct opa_vnic_vema_mad*,struct opa_vnic_vema_mad*) ; 

__attribute__((used)) static void vema_set_class_port_info(struct opa_vnic_vema_port *port,
				     struct opa_vnic_vema_mad *recvd_mad,
				     struct opa_vnic_vema_mad *rsp_mad)
{
	memcpy(&port->class_port_info, recvd_mad->data,
	       sizeof(port->class_port_info));

	vema_get_class_port_info(port, recvd_mad, rsp_mad);
}