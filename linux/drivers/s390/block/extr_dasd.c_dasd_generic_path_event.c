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
struct dasd_device {TYPE_2__* cdev; TYPE_1__* discipline; } ;
struct ccw_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_hpf ) (struct dasd_device*) ;int /*<<< orphan*/  (* kick_validate ) (struct dasd_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_EER_NOPATH ; 
 int /*<<< orphan*/  DASD_STOPPED_DC_WAIT ; 
 int /*<<< orphan*/  DASD_STOPPED_NOT_ACC ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int PE_PATHGROUP_ESTABLISHED ; 
 int PE_PATH_AVAILABLE ; 
 int PE_PATH_GONE ; 
 struct dasd_device* dasd_device_from_cdev_locked (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_device_set_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eer_write (struct dasd_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_path_available (struct dasd_device*,int) ; 
 int dasd_path_get_hpfpm (struct dasd_device*) ; 
 int dasd_path_get_ifccpm (struct dasd_device*) ; 
 int dasd_path_get_opm (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_is_operational (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_path_need_verify (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_path_notoper (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_path_set_tbvpm (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_requeue (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*) ; 
 int /*<<< orphan*/  stub2 (struct dasd_device*) ; 

void dasd_generic_path_event(struct ccw_device *cdev, int *path_event)
{
	struct dasd_device *device;
	int chp, oldopm, hpfpm, ifccpm;

	device = dasd_device_from_cdev_locked(cdev);
	if (IS_ERR(device))
		return;

	oldopm = dasd_path_get_opm(device);
	for (chp = 0; chp < 8; chp++) {
		if (path_event[chp] & PE_PATH_GONE) {
			dasd_path_notoper(device, chp);
		}
		if (path_event[chp] & PE_PATH_AVAILABLE) {
			dasd_path_available(device, chp);
			dasd_schedule_device_bh(device);
		}
		if (path_event[chp] & PE_PATHGROUP_ESTABLISHED) {
			if (!dasd_path_is_operational(device, chp) &&
			    !dasd_path_need_verify(device, chp)) {
				/*
				 * we can not establish a pathgroup on an
				 * unavailable path, so trigger a path
				 * verification first
				 */
			dasd_path_available(device, chp);
			dasd_schedule_device_bh(device);
			}
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				      "Pathgroup re-established\n");
			if (device->discipline->kick_validate)
				device->discipline->kick_validate(device);
		}
	}
	hpfpm = dasd_path_get_hpfpm(device);
	ifccpm = dasd_path_get_ifccpm(device);
	if (!dasd_path_get_opm(device) && hpfpm) {
		/*
		 * device has no operational paths but at least one path is
		 * disabled due to HPF errors
		 * disable HPF at all and use the path(s) again
		 */
		if (device->discipline->disable_hpf)
			device->discipline->disable_hpf(device);
		dasd_device_set_stop_bits(device, DASD_STOPPED_NOT_ACC);
		dasd_path_set_tbvpm(device, hpfpm);
		dasd_schedule_device_bh(device);
		dasd_schedule_requeue(device);
	} else if (!dasd_path_get_opm(device) && ifccpm) {
		/*
		 * device has no operational paths but at least one path is
		 * disabled due to IFCC errors
		 * trigger path verification on paths with IFCC errors
		 */
		dasd_path_set_tbvpm(device, ifccpm);
		dasd_schedule_device_bh(device);
	}
	if (oldopm && !dasd_path_get_opm(device) && !hpfpm && !ifccpm) {
		dev_warn(&device->cdev->dev,
			 "No verified channel paths remain for the device\n");
		DBF_DEV_EVENT(DBF_WARNING, device,
			      "%s", "last verified path gone");
		dasd_eer_write(device, NULL, DASD_EER_NOPATH);
		dasd_device_set_stop_bits(device,
					  DASD_STOPPED_DC_WAIT);
	}
	dasd_put_device(device);
}