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
struct opa_vnic_vema_port {int dummy; } ;
struct opa_vnic_ctrl_port {int num_ports; struct ib_device* ibdev; } ;
struct ib_device {int phys_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  c_info (char*) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct opa_vnic_ctrl_port*) ; 
 struct opa_vnic_ctrl_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_vnic_client ; 
 int /*<<< orphan*/  opa_vnic_ctrl_config_dev (struct opa_vnic_ctrl_port*,int) ; 
 int /*<<< orphan*/  rdma_cap_opa_vnic (struct ib_device*) ; 
 int vema_register (struct opa_vnic_ctrl_port*) ; 

__attribute__((used)) static void opa_vnic_vema_add_one(struct ib_device *device)
{
	struct opa_vnic_ctrl_port *cport;
	int rc, size = sizeof(*cport);

	if (!rdma_cap_opa_vnic(device))
		return;

	size += device->phys_port_cnt * sizeof(struct opa_vnic_vema_port);
	cport = kzalloc(size, GFP_KERNEL);
	if (!cport)
		return;

	cport->num_ports = device->phys_port_cnt;
	cport->ibdev = device;

	/* Initialize opa vnic management agent (vema) */
	rc = vema_register(cport);
	if (!rc)
		c_info("VNIC client initialized\n");

	ib_set_client_data(device, &opa_vnic_client, cport);
	opa_vnic_ctrl_config_dev(cport, true);
}