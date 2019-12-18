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
struct drm_dp_sideband_msg_rx {int* msg; } ;
struct drm_dp_sideband_msg_req_body {int req_type; } ;

/* Variables and functions */
#define  DP_CONNECTION_STATUS_NOTIFY 129 
#define  DP_RESOURCE_STATUS_NOTIFY 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_mst_req_type_str (int) ; 
 int drm_dp_sideband_parse_connection_status_notify (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_req_body*) ; 
 int drm_dp_sideband_parse_resource_status_notify (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_req_body*) ; 
 int /*<<< orphan*/  memset (struct drm_dp_sideband_msg_req_body*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool drm_dp_sideband_parse_req(struct drm_dp_sideband_msg_rx *raw,
				      struct drm_dp_sideband_msg_req_body *msg)
{
	memset(msg, 0, sizeof(*msg));
	msg->req_type = (raw->msg[0] & 0x7f);

	switch (msg->req_type) {
	case DP_CONNECTION_STATUS_NOTIFY:
		return drm_dp_sideband_parse_connection_status_notify(raw, msg);
	case DP_RESOURCE_STATUS_NOTIFY:
		return drm_dp_sideband_parse_resource_status_notify(raw, msg);
	default:
		DRM_ERROR("Got unknown request 0x%02x (%s)\n", msg->req_type,
			  drm_dp_mst_req_type_str(msg->req_type));
		return false;
	}
}