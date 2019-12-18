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
struct irb {int /*<<< orphan*/  scsw; } ;
struct dasd_eckd_private {char suc_reason; scalar_t__ lcu; } ;
struct dasd_device {scalar_t__ state; int features; TYPE_1__* cdev; int /*<<< orphan*/  flags; scalar_t__ block; int /*<<< orphan*/  suc_work; struct dasd_eckd_private* private; } ;
struct dasd_ccw_req {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DASD_FEATURE_FAILONSLCK ; 
 int /*<<< orphan*/  DASD_FLAG_IS_RESERVED ; 
 int /*<<< orphan*/  DASD_FLAG_LOCK_STOLEN ; 
 int /*<<< orphan*/  DASD_FLAG_OFFLINE ; 
 int /*<<< orphan*/  DASD_FLAG_SUC ; 
 int /*<<< orphan*/  DASD_FLAG_SUSPENDED ; 
 char DASD_SENSE_BIT_0 ; 
 char DASD_SIM_SENSE ; 
 scalar_t__ DASD_STATE_ONLINE ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*,...) ; 
 int /*<<< orphan*/  DBF_NOTICE ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 char DEV_STAT_ATTENTION ; 
 char DEV_STAT_DEV_END ; 
 char DEV_STAT_UNIT_CHECK ; 
 char DEV_STAT_UNIT_EXCEP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_3990_erp_handle_sim (struct dasd_device*,char*) ; 
 int /*<<< orphan*/  dasd_generic_handle_state_change (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 char* dasd_get_sense (struct irb*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_reload_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 char scsw_dstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_eckd_check_for_device_change(struct dasd_device *device,
					      struct dasd_ccw_req *cqr,
					      struct irb *irb)
{
	char mask;
	char *sense = NULL;
	struct dasd_eckd_private *private = device->private;

	/* first of all check for state change pending interrupt */
	mask = DEV_STAT_ATTENTION | DEV_STAT_DEV_END | DEV_STAT_UNIT_EXCEP;
	if ((scsw_dstat(&irb->scsw) & mask) == mask) {
		/*
		 * for alias only, not in offline processing
		 * and only if not suspended
		 */
		if (!device->block && private->lcu &&
		    device->state == DASD_STATE_ONLINE &&
		    !test_bit(DASD_FLAG_OFFLINE, &device->flags) &&
		    !test_bit(DASD_FLAG_SUSPENDED, &device->flags)) {
			/* schedule worker to reload device */
			dasd_reload_device(device);
		}
		dasd_generic_handle_state_change(device);
		return;
	}

	sense = dasd_get_sense(irb);
	if (!sense)
		return;

	/* summary unit check */
	if ((sense[27] & DASD_SENSE_BIT_0) && (sense[7] == 0x0D) &&
	    (scsw_dstat(&irb->scsw) & DEV_STAT_UNIT_CHECK)) {
		if (test_and_set_bit(DASD_FLAG_SUC, &device->flags)) {
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				      "eckd suc: device already notified");
			return;
		}
		sense = dasd_get_sense(irb);
		if (!sense) {
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				      "eckd suc: no reason code available");
			clear_bit(DASD_FLAG_SUC, &device->flags);
			return;

		}
		private->suc_reason = sense[8];
		DBF_DEV_EVENT(DBF_NOTICE, device, "%s %x",
			      "eckd handle summary unit check: reason",
			      private->suc_reason);
		dasd_get_device(device);
		if (!schedule_work(&device->suc_work))
			dasd_put_device(device);

		return;
	}

	/* service information message SIM */
	if (!cqr && !(sense[27] & DASD_SENSE_BIT_0) &&
	    ((sense[6] & DASD_SIM_SENSE) == DASD_SIM_SENSE)) {
		dasd_3990_erp_handle_sim(device, sense);
		return;
	}

	/* loss of device reservation is handled via base devices only
	 * as alias devices may be used with several bases
	 */
	if (device->block && (sense[27] & DASD_SENSE_BIT_0) &&
	    (sense[7] == 0x3F) &&
	    (scsw_dstat(&irb->scsw) & DEV_STAT_UNIT_CHECK) &&
	    test_bit(DASD_FLAG_IS_RESERVED, &device->flags)) {
		if (device->features & DASD_FEATURE_FAILONSLCK)
			set_bit(DASD_FLAG_LOCK_STOLEN, &device->flags);
		clear_bit(DASD_FLAG_IS_RESERVED, &device->flags);
		dev_err(&device->cdev->dev,
			"The device reservation was lost\n");
	}
}