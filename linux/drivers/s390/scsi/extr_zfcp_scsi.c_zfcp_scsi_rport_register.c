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
struct zfcp_port {int /*<<< orphan*/  starget_id; struct fc_rport* rport; int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  maxframe_size; scalar_t__ wwpn; TYPE_2__* adapter; int /*<<< orphan*/  d_id; int /*<<< orphan*/  wwnn; } ;
struct fc_rport_identifiers {int /*<<< orphan*/  roles; int /*<<< orphan*/  port_id; scalar_t__ port_name; int /*<<< orphan*/  node_name; } ;
struct fc_rport {int /*<<< orphan*/  scsi_target_id; int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  maxframe_size; } ;
struct TYPE_4__ {TYPE_1__* ccw_device; int /*<<< orphan*/  scsi_host; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RPORT_ROLE_FCP_TARGET ; 
 int /*<<< orphan*/  ZFCP_PSEUDO_ERP_ACTION_RPORT_ADD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 struct fc_rport* fc_remote_port_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_rport_identifiers*) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_trig_lock (char*,TYPE_2__*,struct zfcp_port*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_unit_queue_scsi_scan (struct zfcp_port*) ; 

__attribute__((used)) static void zfcp_scsi_rport_register(struct zfcp_port *port)
{
	struct fc_rport_identifiers ids;
	struct fc_rport *rport;

	if (port->rport)
		return;

	ids.node_name = port->wwnn;
	ids.port_name = port->wwpn;
	ids.port_id = port->d_id;
	ids.roles = FC_RPORT_ROLE_FCP_TARGET;

	zfcp_dbf_rec_trig_lock("scpaddy", port->adapter, port, NULL,
			       ZFCP_PSEUDO_ERP_ACTION_RPORT_ADD,
			       ZFCP_PSEUDO_ERP_ACTION_RPORT_ADD);
	rport = fc_remote_port_add(port->adapter->scsi_host, 0, &ids);
	if (!rport) {
		dev_err(&port->adapter->ccw_device->dev,
			"Registering port 0x%016Lx failed\n",
			(unsigned long long)port->wwpn);
		return;
	}

	rport->maxframe_size = port->maxframe_size;
	rport->supported_classes = port->supported_classes;
	port->rport = rport;
	port->starget_id = rport->scsi_target_id;

	zfcp_unit_queue_scsi_scan(port);
}