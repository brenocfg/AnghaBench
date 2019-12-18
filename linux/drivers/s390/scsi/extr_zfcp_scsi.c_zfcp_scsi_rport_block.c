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
struct zfcp_port {struct fc_rport* rport; int /*<<< orphan*/  adapter; } ;
struct fc_rport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_PSEUDO_ERP_ACTION_RPORT_DEL ; 
 int /*<<< orphan*/  fc_remote_port_delete (struct fc_rport*) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_trig_lock (char*,int /*<<< orphan*/ ,struct zfcp_port*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_scsi_rport_block(struct zfcp_port *port)
{
	struct fc_rport *rport = port->rport;

	if (rport) {
		zfcp_dbf_rec_trig_lock("scpdely", port->adapter, port, NULL,
				       ZFCP_PSEUDO_ERP_ACTION_RPORT_DEL,
				       ZFCP_PSEUDO_ERP_ACTION_RPORT_DEL);
		fc_remote_port_delete(rport);
		port->rport = NULL;
	}
}