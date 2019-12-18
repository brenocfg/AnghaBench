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
typedef  int u32 ;
struct TYPE_2__ {void* get_req; void* change_req; int /*<<< orphan*/  work; } ;
struct vbg_dev {int fixed_events; TYPE_1__ mem_balloon; void* cancel_req; void* ack_events_req; void* mouse_status_req; int /*<<< orphan*/  heartbeat_timer; int /*<<< orphan*/  cancel_req_mutex; int /*<<< orphan*/  session_mutex; int /*<<< orphan*/  event_spinlock; int /*<<< orphan*/  hgcm_wq; int /*<<< orphan*/  event_wq; void* guest_caps_host; void* event_filter_host; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* U32_MAX ; 
 int /*<<< orphan*/  VBG_KERNEL_REQUEST ; 
 int /*<<< orphan*/  VMMDEVREQ_ACKNOWLEDGE_EVENTS ; 
 int /*<<< orphan*/  VMMDEVREQ_CHANGE_MEMBALLOON ; 
 int /*<<< orphan*/  VMMDEVREQ_GET_MEMBALLOON_CHANGE_REQ ; 
 int /*<<< orphan*/  VMMDEVREQ_GET_MOUSE_STATUS ; 
 int /*<<< orphan*/  VMMDEVREQ_HGCM_CANCEL2 ; 
 int VMMDEV_EVENT_HGCM ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_balloon_work ; 
 int vbg_core_set_mouse_status (struct vbg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_err (char*,int) ; 
 int /*<<< orphan*/  vbg_guest_mappings_init (struct vbg_dev*) ; 
 int /*<<< orphan*/  vbg_heartbeat_init (struct vbg_dev*) ; 
 int /*<<< orphan*/  vbg_heartbeat_timer ; 
 int vbg_query_host_version (struct vbg_dev*) ; 
 int vbg_report_driver_status (struct vbg_dev*,int) ; 
 int vbg_report_guest_info (struct vbg_dev*) ; 
 void* vbg_req_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbg_req_free (void*,int) ; 
 int vbg_reset_host_capabilities (struct vbg_dev*) ; 
 int vbg_reset_host_event_filter (struct vbg_dev*,int) ; 

int vbg_core_init(struct vbg_dev *gdev, u32 fixed_events)
{
	int ret = -ENOMEM;

	gdev->fixed_events = fixed_events | VMMDEV_EVENT_HGCM;
	gdev->event_filter_host = U32_MAX;	/* forces a report */
	gdev->guest_caps_host = U32_MAX;	/* forces a report */

	init_waitqueue_head(&gdev->event_wq);
	init_waitqueue_head(&gdev->hgcm_wq);
	spin_lock_init(&gdev->event_spinlock);
	mutex_init(&gdev->session_mutex);
	mutex_init(&gdev->cancel_req_mutex);
	timer_setup(&gdev->heartbeat_timer, vbg_heartbeat_timer, 0);
	INIT_WORK(&gdev->mem_balloon.work, vbg_balloon_work);

	gdev->mem_balloon.get_req =
		vbg_req_alloc(sizeof(*gdev->mem_balloon.get_req),
			      VMMDEVREQ_GET_MEMBALLOON_CHANGE_REQ,
			      VBG_KERNEL_REQUEST);
	gdev->mem_balloon.change_req =
		vbg_req_alloc(sizeof(*gdev->mem_balloon.change_req),
			      VMMDEVREQ_CHANGE_MEMBALLOON,
			      VBG_KERNEL_REQUEST);
	gdev->cancel_req =
		vbg_req_alloc(sizeof(*(gdev->cancel_req)),
			      VMMDEVREQ_HGCM_CANCEL2,
			      VBG_KERNEL_REQUEST);
	gdev->ack_events_req =
		vbg_req_alloc(sizeof(*gdev->ack_events_req),
			      VMMDEVREQ_ACKNOWLEDGE_EVENTS,
			      VBG_KERNEL_REQUEST);
	gdev->mouse_status_req =
		vbg_req_alloc(sizeof(*gdev->mouse_status_req),
			      VMMDEVREQ_GET_MOUSE_STATUS,
			      VBG_KERNEL_REQUEST);

	if (!gdev->mem_balloon.get_req || !gdev->mem_balloon.change_req ||
	    !gdev->cancel_req || !gdev->ack_events_req ||
	    !gdev->mouse_status_req)
		goto err_free_reqs;

	ret = vbg_query_host_version(gdev);
	if (ret)
		goto err_free_reqs;

	ret = vbg_report_guest_info(gdev);
	if (ret) {
		vbg_err("vboxguest: vbg_report_guest_info error: %d\n", ret);
		goto err_free_reqs;
	}

	ret = vbg_reset_host_event_filter(gdev, gdev->fixed_events);
	if (ret) {
		vbg_err("vboxguest: Error setting fixed event filter: %d\n",
			ret);
		goto err_free_reqs;
	}

	ret = vbg_reset_host_capabilities(gdev);
	if (ret) {
		vbg_err("vboxguest: Error clearing guest capabilities: %d\n",
			ret);
		goto err_free_reqs;
	}

	ret = vbg_core_set_mouse_status(gdev, 0);
	if (ret) {
		vbg_err("vboxguest: Error clearing mouse status: %d\n", ret);
		goto err_free_reqs;
	}

	/* These may fail without requiring the driver init to fail. */
	vbg_guest_mappings_init(gdev);
	vbg_heartbeat_init(gdev);

	/* All Done! */
	ret = vbg_report_driver_status(gdev, true);
	if (ret < 0)
		vbg_err("vboxguest: Error reporting driver status: %d\n", ret);

	return 0;

err_free_reqs:
	vbg_req_free(gdev->mouse_status_req,
		     sizeof(*gdev->mouse_status_req));
	vbg_req_free(gdev->ack_events_req,
		     sizeof(*gdev->ack_events_req));
	vbg_req_free(gdev->cancel_req,
		     sizeof(*gdev->cancel_req));
	vbg_req_free(gdev->mem_balloon.change_req,
		     sizeof(*gdev->mem_balloon.change_req));
	vbg_req_free(gdev->mem_balloon.get_req,
		     sizeof(*gdev->mem_balloon.get_req));
	return ret;
}