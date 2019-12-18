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
typedef  enum hdcp_wired_protocol { ____Placeholder_hdcp_wired_protocol } hdcp_wired_protocol ;

/* Variables and functions */
 int HDCP_PROTOCOL_HDMI ; 

__attribute__((used)) static inline
enum hdcp_wired_protocol intel_hdmi_hdcp2_protocol(void)
{
	return HDCP_PROTOCOL_HDMI;
}