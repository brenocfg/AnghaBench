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
struct pvr2_hdw {size_t unit_number; struct pvr2_hdw* mpeg_ctrl_info; struct pvr2_hdw* controls; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/ * vid_stream; struct pvr2_hdw* fw_buffer; int /*<<< orphan*/  encoder_wait_timer; int /*<<< orphan*/  encoder_run_timer; int /*<<< orphan*/  decoder_stabilization_timer; int /*<<< orphan*/  quiescent_timer; int /*<<< orphan*/  workpoll; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 size_t PVR_NUM ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_hdw_remove_usb_stuff (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_i2c_core_done (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_stream_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_unit_mtx ; 
 struct pvr2_hdw** unit_pointers ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

void pvr2_hdw_destroy(struct pvr2_hdw *hdw)
{
	if (!hdw) return;
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_destroy: hdw=%p",hdw);
	flush_work(&hdw->workpoll);
	del_timer_sync(&hdw->quiescent_timer);
	del_timer_sync(&hdw->decoder_stabilization_timer);
	del_timer_sync(&hdw->encoder_run_timer);
	del_timer_sync(&hdw->encoder_wait_timer);
	if (hdw->fw_buffer) {
		kfree(hdw->fw_buffer);
		hdw->fw_buffer = NULL;
	}
	if (hdw->vid_stream) {
		pvr2_stream_destroy(hdw->vid_stream);
		hdw->vid_stream = NULL;
	}
	pvr2_i2c_core_done(hdw);
	v4l2_device_unregister(&hdw->v4l2_dev);
	pvr2_hdw_remove_usb_stuff(hdw);
	mutex_lock(&pvr2_unit_mtx);
	do {
		if ((hdw->unit_number >= 0) &&
		    (hdw->unit_number < PVR_NUM) &&
		    (unit_pointers[hdw->unit_number] == hdw)) {
			unit_pointers[hdw->unit_number] = NULL;
		}
	} while (0);
	mutex_unlock(&pvr2_unit_mtx);
	kfree(hdw->controls);
	kfree(hdw->mpeg_ctrl_info);
	kfree(hdw);
}