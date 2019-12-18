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
struct fnic {int /*<<< orphan*/  stats_reset_time; TYPE_1__* lport; int /*<<< orphan*/  fnic_lock; int /*<<< orphan*/  vdev; } ;
struct fc_lport {int dummy; } ;
struct fc_host_statistics {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNIC_MAIN_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  fnic_dump_fchost_stats (struct Scsi_Host*,struct fc_host_statistics*) ; 
 struct fc_host_statistics* fnic_get_stats (struct Scsi_Host*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct fnic* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  memset (struct fc_host_statistics*,int /*<<< orphan*/ ,int) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vnic_dev_stats_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fnic_reset_host_stats(struct Scsi_Host *host)
{
	int ret;
	struct fc_lport *lp = shost_priv(host);
	struct fnic *fnic = lport_priv(lp);
	struct fc_host_statistics *stats;
	unsigned long flags;

	/* dump current stats, before clearing them */
	stats = fnic_get_stats(host);
	fnic_dump_fchost_stats(host, stats);

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	ret = vnic_dev_stats_clear(fnic->vdev);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	if (ret) {
		FNIC_MAIN_DBG(KERN_DEBUG, fnic->lport->host,
				"fnic: Reset vnic stats failed"
				" 0x%x", ret);
		return;
	}
	fnic->stats_reset_time = jiffies;
	memset(stats, 0, sizeof(*stats));

	return;
}