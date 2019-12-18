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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct us_data {scalar_t__ transport; int fflags; int max_lun; TYPE_1__* pusb_intf; int /*<<< orphan*/  scan_dwork; int /*<<< orphan*/  dflags; int /*<<< orphan*/  scsi_name; int /*<<< orphan*/  protocol_name; int /*<<< orphan*/  transport_name; int /*<<< orphan*/  proto_handler; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int this_id; int max_id; int no_scsi2_lun_in_cdb; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int HZ ; 
 int /*<<< orphan*/  US_FLIDX_REDO_READ10 ; 
 int /*<<< orphan*/  US_FLIDX_SCAN_PENDING ; 
 int US_FL_INITIAL_READ10 ; 
 int US_FL_SCM_MULT_TARG ; 
 int US_FL_SINGLE_LUN ; 
 int delay_use ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int get_pipes (struct us_data*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_everything (struct us_data*) ; 
 int scsi_add_host (TYPE_3__*,struct device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  system_freezable_wq ; 
 TYPE_3__* us_to_host (struct us_data*) ; 
 int /*<<< orphan*/  usb_autopm_get_interface_no_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_no_suspend (TYPE_1__*) ; 
 scalar_t__ usb_stor_Bulk_transport ; 
 int usb_stor_acquire_resources (struct us_data*) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

int usb_stor_probe2(struct us_data *us)
{
	int result;
	struct device *dev = &us->pusb_intf->dev;

	/* Make sure the transport and protocol have both been set */
	if (!us->transport || !us->proto_handler) {
		result = -ENXIO;
		goto BadDevice;
	}
	usb_stor_dbg(us, "Transport: %s\n", us->transport_name);
	usb_stor_dbg(us, "Protocol: %s\n", us->protocol_name);

	if (us->fflags & US_FL_SCM_MULT_TARG) {
		/*
		 * SCM eUSCSI bridge devices can have different numbers
		 * of LUNs on different targets; allow all to be probed.
		 */
		us->max_lun = 7;
		/* The eUSCSI itself has ID 7, so avoid scanning that */
		us_to_host(us)->this_id = 7;
		/* max_id is 8 initially, so no need to set it here */
	} else {
		/* In the normal case there is only a single target */
		us_to_host(us)->max_id = 1;
		/*
		 * Like Windows, we won't store the LUN bits in CDB[1] for
		 * SCSI-2 devices using the Bulk-Only transport (even though
		 * this violates the SCSI spec).
		 */
		if (us->transport == usb_stor_Bulk_transport)
			us_to_host(us)->no_scsi2_lun_in_cdb = 1;
	}

	/* fix for single-lun devices */
	if (us->fflags & US_FL_SINGLE_LUN)
		us->max_lun = 0;

	/* Find the endpoints and calculate pipe values */
	result = get_pipes(us);
	if (result)
		goto BadDevice;

	/*
	 * If the device returns invalid data for the first READ(10)
	 * command, indicate the command should be retried.
	 */
	if (us->fflags & US_FL_INITIAL_READ10)
		set_bit(US_FLIDX_REDO_READ10, &us->dflags);

	/* Acquire all the other resources and add the host */
	result = usb_stor_acquire_resources(us);
	if (result)
		goto BadDevice;
	usb_autopm_get_interface_no_resume(us->pusb_intf);
	snprintf(us->scsi_name, sizeof(us->scsi_name), "usb-storage %s",
					dev_name(&us->pusb_intf->dev));
	result = scsi_add_host(us_to_host(us), dev);
	if (result) {
		dev_warn(dev,
				"Unable to add the scsi host\n");
		goto HostAddErr;
	}

	/* Submit the delayed_work for SCSI-device scanning */
	set_bit(US_FLIDX_SCAN_PENDING, &us->dflags);

	if (delay_use > 0)
		dev_dbg(dev, "waiting for device to settle before scanning\n");
	queue_delayed_work(system_freezable_wq, &us->scan_dwork,
			delay_use * HZ);
	return 0;

	/* We come here if there are any problems */
HostAddErr:
	usb_autopm_put_interface_no_suspend(us->pusb_intf);
BadDevice:
	usb_stor_dbg(us, "storage_probe() failed\n");
	release_everything(us);
	return result;
}