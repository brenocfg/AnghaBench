#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lpum; } ;
struct TYPE_6__ {TYPE_1__ esw1; } ;
struct TYPE_8__ {scalar_t__ sesq; } ;
struct TYPE_7__ {TYPE_4__ tm; } ;
struct irb {TYPE_2__ esw; TYPE_3__ scsw; } ;
struct dasd_eckd_private {int /*<<< orphan*/  fcx_max_data; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STOPPED_NOT_ACC ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 scalar_t__ SCSW_SESQ_DEV_NOFCX ; 
 scalar_t__ SCSW_SESQ_PATH_NOFCX ; 
 int /*<<< orphan*/  dasd_device_set_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eckd_disable_hpf_device (struct dasd_device*) ; 
 scalar_t__ dasd_eckd_disable_hpf_path (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_path_get_hpfpm (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_set_tbvpm (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_schedule_requeue (struct dasd_device*) ; 

__attribute__((used)) static void dasd_eckd_handle_hpf_error(struct dasd_device *device,
				       struct irb *irb)
{
	struct dasd_eckd_private *private = device->private;

	if (!private->fcx_max_data) {
		/* sanity check for no HPF, the error makes no sense */
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "Trying to disable HPF for a non HPF device");
		return;
	}
	if (irb->scsw.tm.sesq == SCSW_SESQ_DEV_NOFCX) {
		dasd_eckd_disable_hpf_device(device);
	} else if (irb->scsw.tm.sesq == SCSW_SESQ_PATH_NOFCX) {
		if (dasd_eckd_disable_hpf_path(device, irb->esw.esw1.lpum))
			return;
		dasd_eckd_disable_hpf_device(device);
		dasd_path_set_tbvpm(device,
				  dasd_path_get_hpfpm(device));
	}
	/*
	 * prevent that any new I/O ist started on the device and schedule a
	 * requeue of existing requests
	 */
	dasd_device_set_stop_bits(device, DASD_STOPPED_NOT_ACC);
	dasd_schedule_requeue(device);
}