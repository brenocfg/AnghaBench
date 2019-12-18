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
struct reset_stats {int /*<<< orphan*/  fnic_reset_failures; int /*<<< orphan*/  fnic_reset_completions; int /*<<< orphan*/  fnic_resets; } ;
struct TYPE_3__ {struct reset_stats reset_stats; } ;
struct fnic {TYPE_2__* lport; TYPE_1__ fnic_stats; } ;
struct fc_lport {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int fc_lport_reset (struct fc_lport*) ; 
 struct fnic* lport_priv (struct fc_lport*) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 

int fnic_reset(struct Scsi_Host *shost)
{
	struct fc_lport *lp;
	struct fnic *fnic;
	int ret = 0;
	struct reset_stats *reset_stats;

	lp = shost_priv(shost);
	fnic = lport_priv(lp);
	reset_stats = &fnic->fnic_stats.reset_stats;

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "fnic_reset called\n");

	atomic64_inc(&reset_stats->fnic_resets);

	/*
	 * Reset local port, this will clean up libFC exchanges,
	 * reset remote port sessions, and if link is up, begin flogi
	 */
	ret = fc_lport_reset(lp);

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "Returning from fnic reset %s\n",
		      (ret == 0) ?
		      "SUCCESS" : "FAILED");

	if (ret == 0)
		atomic64_inc(&reset_stats->fnic_reset_completions);
	else
		atomic64_inc(&reset_stats->fnic_reset_failures);

	return ret;
}