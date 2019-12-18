#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zfcp_port {scalar_t__ wwpn; int /*<<< orphan*/  dev; int /*<<< orphan*/  status; scalar_t__ wwnn; } ;
struct TYPE_6__ {scalar_t__ status; struct zfcp_port* port; } ;
struct fc_els_adisc {int /*<<< orphan*/  adisc_wwpn; int /*<<< orphan*/  adisc_wwnn; } ;
struct TYPE_4__ {struct fc_els_adisc rsp; } ;
struct TYPE_5__ {TYPE_1__ adisc; } ;
struct zfcp_fc_req {TYPE_3__ ct_els; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int /*<<< orphan*/  ZFCP_STATUS_PORT_LINK_TEST ; 
 int /*<<< orphan*/  atomic_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct zfcp_fc_req*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_port_forced_reopen (struct zfcp_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_port_reopen (struct zfcp_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_fc_req_cache ; 
 int /*<<< orphan*/  zfcp_scsi_schedule_rport_register (struct zfcp_port*) ; 

__attribute__((used)) static void zfcp_fc_adisc_handler(void *data)
{
	struct zfcp_fc_req *fc_req = data;
	struct zfcp_port *port = fc_req->ct_els.port;
	struct fc_els_adisc *adisc_resp = &fc_req->u.adisc.rsp;

	if (fc_req->ct_els.status) {
		/* request rejected or timed out */
		zfcp_erp_port_forced_reopen(port, ZFCP_STATUS_COMMON_ERP_FAILED,
					    "fcadh_1");
		goto out;
	}

	if (!port->wwnn)
		port->wwnn = be64_to_cpu(adisc_resp->adisc_wwnn);

	if ((port->wwpn != be64_to_cpu(adisc_resp->adisc_wwpn)) ||
	    !(atomic_read(&port->status) & ZFCP_STATUS_COMMON_OPEN)) {
		zfcp_erp_port_reopen(port, ZFCP_STATUS_COMMON_ERP_FAILED,
				     "fcadh_2");
		goto out;
	}

	/* port is good, unblock rport without going through erp */
	zfcp_scsi_schedule_rport_register(port);
 out:
	atomic_andnot(ZFCP_STATUS_PORT_LINK_TEST, &port->status);
	put_device(&port->dev);
	kmem_cache_free(zfcp_fc_req_cache, fc_req);
}