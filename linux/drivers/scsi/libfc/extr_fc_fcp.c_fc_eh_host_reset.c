#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* device; } ;
struct fc_lport {int /*<<< orphan*/  port_id; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAILED ; 
 unsigned long FC_HOST_RESET_TIMEOUT ; 
 int /*<<< orphan*/  FC_SCSI_DBG (struct fc_lport*,char*) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SUCCESS ; 
 scalar_t__ fc_fcp_lport_queue_ready (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_reset (struct fc_lport*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,int /*<<< orphan*/ ) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

int fc_eh_host_reset(struct scsi_cmnd *sc_cmd)
{
	struct Scsi_Host *shost = sc_cmd->device->host;
	struct fc_lport *lport = shost_priv(shost);
	unsigned long wait_tmo;

	FC_SCSI_DBG(lport, "Resetting host\n");

	fc_lport_reset(lport);
	wait_tmo = jiffies + FC_HOST_RESET_TIMEOUT;
	while (!fc_fcp_lport_queue_ready(lport) && time_before(jiffies,
							       wait_tmo))
		msleep(1000);

	if (fc_fcp_lport_queue_ready(lport)) {
		shost_printk(KERN_INFO, shost, "libfc: Host reset succeeded "
			     "on port (%6.6x)\n", lport->port_id);
		return SUCCESS;
	} else {
		shost_printk(KERN_INFO, shost, "libfc: Host reset failed, "
			     "port (%6.6x) is not ready.\n",
			     lport->port_id);
		return FAILED;
	}
}