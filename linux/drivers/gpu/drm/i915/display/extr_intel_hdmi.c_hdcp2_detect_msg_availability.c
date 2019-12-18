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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int HDCP_2_2_HDMI_RXSTATUS_LEN ; 
 int HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI (int) ; 
 scalar_t__ HDCP_2_2_HDMI_RXSTATUS_READY (int) ; 
 int HDCP_2_2_REP_SEND_RECVID_LIST ; 
 int intel_hdmi_hdcp2_read_rx_status (struct intel_digital_port*,int*) ; 

__attribute__((used)) static inline
int hdcp2_detect_msg_availability(struct intel_digital_port *intel_digital_port,
				  u8 msg_id, bool *msg_ready,
				  ssize_t *msg_sz)
{
	u8 rx_status[HDCP_2_2_HDMI_RXSTATUS_LEN];
	int ret;

	ret = intel_hdmi_hdcp2_read_rx_status(intel_digital_port, rx_status);
	if (ret < 0) {
		DRM_DEBUG_KMS("rx_status read failed. Err %d\n", ret);
		return ret;
	}

	*msg_sz = ((HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(rx_status[1]) << 8) |
		  rx_status[0]);

	if (msg_id == HDCP_2_2_REP_SEND_RECVID_LIST)
		*msg_ready = (HDCP_2_2_HDMI_RXSTATUS_READY(rx_status[1]) &&
			     *msg_sz);
	else
		*msg_ready = *msg_sz;

	return 0;
}