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
struct vmmdev_request_header {int request_type; } ;
struct vmmdev_guest_status {int facility; } ;
struct vbg_session {int requestor; } ;
struct vbg_dev {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
#define  VBOXGUEST_FACILITY_TYPE_ALL 170 
#define  VBOXGUEST_FACILITY_TYPE_GRAPHICS 169 
#define  VBOXGUEST_FACILITY_TYPE_SEAMLESS 168 
#define  VBOXGUEST_FACILITY_TYPE_VBOXGUEST_DRIVER 167 
#define  VBOXGUEST_FACILITY_TYPE_VBOX_SERVICE 166 
#define  VBOXGUEST_FACILITY_TYPE_VBOX_TRAY_CLIENT 165 
#define  VMMDEVREQ_ACKNOWLEDGE_EVENTS 164 
#define  VMMDEVREQ_CHECK_SHARED_MODULES 163 
#define  VMMDEVREQ_CTL_GUEST_FILTER_MASK 162 
#define  VMMDEVREQ_DEBUG_IS_PAGE_SHARED 161 
#define  VMMDEVREQ_GET_CPU_HOTPLUG_REQ 160 
#define  VMMDEVREQ_GET_DISPLAY_CHANGE_REQ 159 
#define  VMMDEVREQ_GET_DISPLAY_CHANGE_REQ2 158 
#define  VMMDEVREQ_GET_DISPLAY_CHANGE_REQEX 157 
#define  VMMDEVREQ_GET_HEIGHT_REDUCTION 156 
#define  VMMDEVREQ_GET_HOST_TIME 155 
#define  VMMDEVREQ_GET_HOST_VERSION 154 
#define  VMMDEVREQ_GET_MOUSE_STATUS 153 
#define  VMMDEVREQ_GET_PAGE_SHARING_STATUS 152 
#define  VMMDEVREQ_GET_SEAMLESS_CHANGE_REQ 151 
#define  VMMDEVREQ_GET_SESSION_ID 150 
#define  VMMDEVREQ_GET_STATISTICS_CHANGE_REQ 149 
#define  VMMDEVREQ_GET_VRDPCHANGE_REQ 148 
#define  VMMDEVREQ_IDLE 147 
#define  VMMDEVREQ_LOG_STRING 146 
#define  VMMDEVREQ_QUERY_CREDENTIALS 145 
#define  VMMDEVREQ_REGISTER_SHARED_MODULE 144 
#define  VMMDEVREQ_REPORT_CREDENTIALS_JUDGEMENT 143 
#define  VMMDEVREQ_REPORT_GUEST_CAPABILITIES 142 
#define  VMMDEVREQ_REPORT_GUEST_STATS 141 
#define  VMMDEVREQ_REPORT_GUEST_STATUS 140 
#define  VMMDEVREQ_REPORT_GUEST_USER_STATE 139 
#define  VMMDEVREQ_SET_CPU_HOTPLUG_STATUS 138 
#define  VMMDEVREQ_SET_MOUSE_STATUS 137 
#define  VMMDEVREQ_SET_POINTER_SHAPE 136 
#define  VMMDEVREQ_SET_POWER_STATUS 135 
#define  VMMDEVREQ_UNREGISTER_SHARED_MODULE 134 
#define  VMMDEVREQ_VIDEMODE_SUPPORTED 133 
#define  VMMDEVREQ_VIDEMODE_SUPPORTED2 132 
#define  VMMDEVREQ_VIDEO_ACCEL_ENABLE 131 
#define  VMMDEVREQ_VIDEO_ACCEL_FLUSH 130 
#define  VMMDEVREQ_VIDEO_SET_VISIBLE_REGION 129 
#define  VMMDEVREQ_WRITE_COREDUMP 128 
 int VMMDEV_REQUESTOR_USER_DEVICE ; 
 int /*<<< orphan*/  vbg_err (char*,int) ; 

__attribute__((used)) static int vbg_req_allowed(struct vbg_dev *gdev, struct vbg_session *session,
			   const struct vmmdev_request_header *req)
{
	const struct vmmdev_guest_status *guest_status;
	bool trusted_apps_only;

	switch (req->request_type) {
	/* Trusted users apps only. */
	case VMMDEVREQ_QUERY_CREDENTIALS:
	case VMMDEVREQ_REPORT_CREDENTIALS_JUDGEMENT:
	case VMMDEVREQ_REGISTER_SHARED_MODULE:
	case VMMDEVREQ_UNREGISTER_SHARED_MODULE:
	case VMMDEVREQ_WRITE_COREDUMP:
	case VMMDEVREQ_GET_CPU_HOTPLUG_REQ:
	case VMMDEVREQ_SET_CPU_HOTPLUG_STATUS:
	case VMMDEVREQ_CHECK_SHARED_MODULES:
	case VMMDEVREQ_GET_PAGE_SHARING_STATUS:
	case VMMDEVREQ_DEBUG_IS_PAGE_SHARED:
	case VMMDEVREQ_REPORT_GUEST_STATS:
	case VMMDEVREQ_REPORT_GUEST_USER_STATE:
	case VMMDEVREQ_GET_STATISTICS_CHANGE_REQ:
		trusted_apps_only = true;
		break;

	/* Anyone. */
	case VMMDEVREQ_GET_MOUSE_STATUS:
	case VMMDEVREQ_SET_MOUSE_STATUS:
	case VMMDEVREQ_SET_POINTER_SHAPE:
	case VMMDEVREQ_GET_HOST_VERSION:
	case VMMDEVREQ_IDLE:
	case VMMDEVREQ_GET_HOST_TIME:
	case VMMDEVREQ_SET_POWER_STATUS:
	case VMMDEVREQ_ACKNOWLEDGE_EVENTS:
	case VMMDEVREQ_CTL_GUEST_FILTER_MASK:
	case VMMDEVREQ_REPORT_GUEST_STATUS:
	case VMMDEVREQ_GET_DISPLAY_CHANGE_REQ:
	case VMMDEVREQ_VIDEMODE_SUPPORTED:
	case VMMDEVREQ_GET_HEIGHT_REDUCTION:
	case VMMDEVREQ_GET_DISPLAY_CHANGE_REQ2:
	case VMMDEVREQ_VIDEMODE_SUPPORTED2:
	case VMMDEVREQ_VIDEO_ACCEL_ENABLE:
	case VMMDEVREQ_VIDEO_ACCEL_FLUSH:
	case VMMDEVREQ_VIDEO_SET_VISIBLE_REGION:
	case VMMDEVREQ_GET_DISPLAY_CHANGE_REQEX:
	case VMMDEVREQ_GET_SEAMLESS_CHANGE_REQ:
	case VMMDEVREQ_GET_VRDPCHANGE_REQ:
	case VMMDEVREQ_LOG_STRING:
	case VMMDEVREQ_GET_SESSION_ID:
		trusted_apps_only = false;
		break;

	/* Depends on the request parameters... */
	case VMMDEVREQ_REPORT_GUEST_CAPABILITIES:
		guest_status = (const struct vmmdev_guest_status *)req;
		switch (guest_status->facility) {
		case VBOXGUEST_FACILITY_TYPE_ALL:
		case VBOXGUEST_FACILITY_TYPE_VBOXGUEST_DRIVER:
			vbg_err("Denying userspace vmm report guest cap. call facility %#08x\n",
				guest_status->facility);
			return -EPERM;
		case VBOXGUEST_FACILITY_TYPE_VBOX_SERVICE:
			trusted_apps_only = true;
			break;
		case VBOXGUEST_FACILITY_TYPE_VBOX_TRAY_CLIENT:
		case VBOXGUEST_FACILITY_TYPE_SEAMLESS:
		case VBOXGUEST_FACILITY_TYPE_GRAPHICS:
		default:
			trusted_apps_only = false;
			break;
		}
		break;

	/* Anything else is not allowed. */
	default:
		vbg_err("Denying userspace vmm call type %#08x\n",
			req->request_type);
		return -EPERM;
	}

	if (trusted_apps_only &&
	    (session->requestor & VMMDEV_REQUESTOR_USER_DEVICE)) {
		vbg_err("Denying userspace vmm call type %#08x through vboxuser device node\n",
			req->request_type);
		return -EPERM;
	}

	return 0;
}