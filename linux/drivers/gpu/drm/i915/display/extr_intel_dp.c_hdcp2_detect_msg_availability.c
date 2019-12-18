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
typedef  int u8 ;
struct intel_digital_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
#define  HDCP_2_2_AKE_SEND_HPRIME 130 
#define  HDCP_2_2_AKE_SEND_PAIRING_INFO 129 
 int /*<<< orphan*/  HDCP_2_2_DP_RXSTATUS_H_PRIME (int) ; 
 int /*<<< orphan*/  HDCP_2_2_DP_RXSTATUS_PAIRING (int) ; 
 int /*<<< orphan*/  HDCP_2_2_DP_RXSTATUS_READY (int) ; 
#define  HDCP_2_2_REP_SEND_RECVID_LIST 128 
 int intel_dp_hdcp2_read_rx_status (struct intel_digital_port*,int*) ; 

__attribute__((used)) static
int hdcp2_detect_msg_availability(struct intel_digital_port *intel_dig_port,
				  u8 msg_id, bool *msg_ready)
{
	u8 rx_status;
	int ret;

	*msg_ready = false;
	ret = intel_dp_hdcp2_read_rx_status(intel_dig_port, &rx_status);
	if (ret < 0)
		return ret;

	switch (msg_id) {
	case HDCP_2_2_AKE_SEND_HPRIME:
		if (HDCP_2_2_DP_RXSTATUS_H_PRIME(rx_status))
			*msg_ready = true;
		break;
	case HDCP_2_2_AKE_SEND_PAIRING_INFO:
		if (HDCP_2_2_DP_RXSTATUS_PAIRING(rx_status))
			*msg_ready = true;
		break;
	case HDCP_2_2_REP_SEND_RECVID_LIST:
		if (HDCP_2_2_DP_RXSTATUS_READY(rx_status))
			*msg_ready = true;
		break;
	default:
		DRM_ERROR("Unidentified msg_id: %d\n", msg_id);
		return -EINVAL;
	}

	return 0;
}