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
struct srp_rport {scalar_t__ fast_io_fail_tmo; scalar_t__ dev_loss_tmo; } ;
struct srp_internal {TYPE_1__* f; } ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; struct Scsi_Host* host; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;
struct TYPE_2__ {scalar_t__ reset_timer_if_blocked; } ;

/* Variables and functions */
 int BLK_EH_DONE ; 
 int BLK_EH_RESET_TIMER ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_device_blocked (struct scsi_device*) ; 
 struct srp_rport* shost_to_rport (struct Scsi_Host*) ; 
 struct srp_internal* to_srp_internal (int /*<<< orphan*/ ) ; 

enum blk_eh_timer_return srp_timed_out(struct scsi_cmnd *scmd)
{
	struct scsi_device *sdev = scmd->device;
	struct Scsi_Host *shost = sdev->host;
	struct srp_internal *i = to_srp_internal(shost->transportt);
	struct srp_rport *rport = shost_to_rport(shost);

	pr_debug("timeout for sdev %s\n", dev_name(&sdev->sdev_gendev));
	return rport && rport->fast_io_fail_tmo < 0 &&
		rport->dev_loss_tmo < 0 &&
		i->f->reset_timer_if_blocked && scsi_device_blocked(sdev) ?
		BLK_EH_RESET_TIMER : BLK_EH_DONE;
}