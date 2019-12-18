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
typedef  int uint32_t ;
typedef  enum hdmi_hdcp_key_state { ____Placeholder_hdmi_hdcp_key_state } hdmi_hdcp_key_state ;

/* Variables and functions */
 int HDMI_HDCP_LINK0_STATUS_KEY_STATE__MASK ; 
 int HDMI_HDCP_LINK0_STATUS_KEY_STATE__SHIFT ; 

__attribute__((used)) static inline uint32_t HDMI_HDCP_LINK0_STATUS_KEY_STATE(enum hdmi_hdcp_key_state val)
{
	return ((val) << HDMI_HDCP_LINK0_STATUS_KEY_STATE__SHIFT) & HDMI_HDCP_LINK0_STATUS_KEY_STATE__MASK;
}