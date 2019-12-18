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
struct pvr2_hdw {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  PVR2_TRACE_INFO ; 
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 int init_pause_msec ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int usb_lock_device_for_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_reset_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_device (int /*<<< orphan*/ ) ; 

void pvr2_hdw_device_reset(struct pvr2_hdw *hdw)
{
	int ret;
	pvr2_trace(PVR2_TRACE_INIT,"Performing a device reset...");
	ret = usb_lock_device_for_reset(hdw->usb_dev,NULL);
	if (ret == 0) {
		ret = usb_reset_device(hdw->usb_dev);
		usb_unlock_device(hdw->usb_dev);
	} else {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Failed to lock USB device ret=%d",ret);
	}
	if (init_pause_msec) {
		pvr2_trace(PVR2_TRACE_INFO,
			   "Waiting %u msec for hardware to settle",
			   init_pause_msec);
		msleep(init_pause_msec);
	}

}