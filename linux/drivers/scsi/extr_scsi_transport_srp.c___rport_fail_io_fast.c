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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct srp_rport {TYPE_1__ dev; int /*<<< orphan*/  mutex; } ;
struct srp_internal {TYPE_2__* f; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* terminate_rport_io ) (struct srp_rport*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_TRANSPORT_OFFLINE ; 
 int /*<<< orphan*/  SRP_RPORT_FAIL_FAST ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* rport_to_shost (struct srp_rport*) ; 
 int /*<<< orphan*/  scsi_target_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_target_unblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ srp_rport_set_state (struct srp_rport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct srp_rport*) ; 
 struct srp_internal* to_srp_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rport_fail_io_fast(struct srp_rport *rport)
{
	struct Scsi_Host *shost = rport_to_shost(rport);
	struct srp_internal *i;

	lockdep_assert_held(&rport->mutex);

	if (srp_rport_set_state(rport, SRP_RPORT_FAIL_FAST))
		return;
	/*
	 * Call scsi_target_block() to wait for ongoing shost->queuecommand()
	 * calls before invoking i->f->terminate_rport_io().
	 */
	scsi_target_block(rport->dev.parent);
	scsi_target_unblock(rport->dev.parent, SDEV_TRANSPORT_OFFLINE);

	/* Involve the LLD if possible to terminate all I/O on the rport. */
	i = to_srp_internal(shost->transportt);
	if (i->f->terminate_rport_io)
		i->f->terminate_rport_io(rport);
}