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
struct drm_dp_sideband_msg_rx {int* msg; } ;
struct TYPE_3__ {int reason; int nak_data; int /*<<< orphan*/  guid; } ;
struct TYPE_4__ {TYPE_1__ nak; } ;
struct drm_dp_sideband_msg_reply_body {int reply_type; int req_type; TYPE_2__ u; } ;

/* Variables and functions */
#define  DP_ALLOCATE_PAYLOAD 136 
#define  DP_ENUM_PATH_RESOURCES 135 
#define  DP_LINK_ADDRESS 134 
#define  DP_POWER_DOWN_PHY 133 
#define  DP_POWER_UP_PHY 132 
#define  DP_QUERY_PAYLOAD 131 
#define  DP_REMOTE_DPCD_READ 130 
#define  DP_REMOTE_DPCD_WRITE 129 
#define  DP_REMOTE_I2C_READ 128 
 int DP_SIDEBAND_REPLY_NAK ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_mst_req_type_str (int) ; 
 int drm_dp_sideband_parse_allocate_payload_ack (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_reply_body*) ; 
 int drm_dp_sideband_parse_enum_path_resources_ack (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_reply_body*) ; 
 int drm_dp_sideband_parse_link_address (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_reply_body*) ; 
 int drm_dp_sideband_parse_power_updown_phy_ack (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_reply_body*) ; 
 int drm_dp_sideband_parse_query_payload_ack (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_reply_body*) ; 
 int drm_dp_sideband_parse_remote_dpcd_read (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_reply_body*) ; 
 int drm_dp_sideband_parse_remote_dpcd_write (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_reply_body*) ; 
 int drm_dp_sideband_parse_remote_i2c_read_ack (struct drm_dp_sideband_msg_rx*,struct drm_dp_sideband_msg_reply_body*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (struct drm_dp_sideband_msg_reply_body*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool drm_dp_sideband_parse_reply(struct drm_dp_sideband_msg_rx *raw,
					struct drm_dp_sideband_msg_reply_body *msg)
{
	memset(msg, 0, sizeof(*msg));
	msg->reply_type = (raw->msg[0] & 0x80) >> 7;
	msg->req_type = (raw->msg[0] & 0x7f);

	if (msg->reply_type == DP_SIDEBAND_REPLY_NAK) {
		memcpy(msg->u.nak.guid, &raw->msg[1], 16);
		msg->u.nak.reason = raw->msg[17];
		msg->u.nak.nak_data = raw->msg[18];
		return false;
	}

	switch (msg->req_type) {
	case DP_LINK_ADDRESS:
		return drm_dp_sideband_parse_link_address(raw, msg);
	case DP_QUERY_PAYLOAD:
		return drm_dp_sideband_parse_query_payload_ack(raw, msg);
	case DP_REMOTE_DPCD_READ:
		return drm_dp_sideband_parse_remote_dpcd_read(raw, msg);
	case DP_REMOTE_DPCD_WRITE:
		return drm_dp_sideband_parse_remote_dpcd_write(raw, msg);
	case DP_REMOTE_I2C_READ:
		return drm_dp_sideband_parse_remote_i2c_read_ack(raw, msg);
	case DP_ENUM_PATH_RESOURCES:
		return drm_dp_sideband_parse_enum_path_resources_ack(raw, msg);
	case DP_ALLOCATE_PAYLOAD:
		return drm_dp_sideband_parse_allocate_payload_ack(raw, msg);
	case DP_POWER_DOWN_PHY:
	case DP_POWER_UP_PHY:
		return drm_dp_sideband_parse_power_updown_phy_ack(raw, msg);
	default:
		DRM_ERROR("Got unknown reply 0x%02x (%s)\n", msg->req_type,
			  drm_dp_mst_req_type_str(msg->req_type));
		return false;
	}
}