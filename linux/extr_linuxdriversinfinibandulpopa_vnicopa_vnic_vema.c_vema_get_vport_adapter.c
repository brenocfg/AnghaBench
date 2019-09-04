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
typedef  int /*<<< orphan*/  u8 ;
struct opa_vnic_vema_port {int /*<<< orphan*/  vport_idr; } ;
struct opa_vnic_vema_mad {int dummy; } ;
struct opa_vnic_adapter {int dummy; } ;

/* Variables and functions */
 struct opa_vnic_adapter* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vema_get_vport_num (struct opa_vnic_vema_mad*) ; 

__attribute__((used)) static inline struct opa_vnic_adapter *
vema_get_vport_adapter(struct opa_vnic_vema_mad *recvd_mad,
		       struct opa_vnic_vema_port *port)
{
	u8 vport_num = vema_get_vport_num(recvd_mad);

	return idr_find(&port->vport_idr, vport_num);
}