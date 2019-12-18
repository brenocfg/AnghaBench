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
typedef  int /*<<< orphan*/  u8 ;
struct intel_digital_port {int dummy; } ;

/* Variables and functions */
 int HDCP_2_2_HDMI_RXSTATUS_LEN ; 
 scalar_t__ HDCP_2_2_HDMI_RXSTATUS_READY (int /*<<< orphan*/ ) ; 
 scalar_t__ HDCP_2_2_HDMI_RXSTATUS_REAUTH_REQ (int /*<<< orphan*/ ) ; 
 int HDCP_REAUTH_REQUEST ; 
 int HDCP_TOPOLOGY_CHANGE ; 
 int intel_hdmi_hdcp2_read_rx_status (struct intel_digital_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int intel_hdmi_hdcp2_check_link(struct intel_digital_port *intel_dig_port)
{
	u8 rx_status[HDCP_2_2_HDMI_RXSTATUS_LEN];
	int ret;

	ret = intel_hdmi_hdcp2_read_rx_status(intel_dig_port, rx_status);
	if (ret)
		return ret;

	/*
	 * Re-auth request and Link Integrity Failures are represented by
	 * same bit. i.e reauth_req.
	 */
	if (HDCP_2_2_HDMI_RXSTATUS_REAUTH_REQ(rx_status[1]))
		ret = HDCP_REAUTH_REQUEST;
	else if (HDCP_2_2_HDMI_RXSTATUS_READY(rx_status[1]))
		ret = HDCP_TOPOLOGY_CHANGE;

	return ret;
}