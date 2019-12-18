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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int,int) ; 
 int __wait_for (int,int,int,int,int) ; 
 int get_hdcp2_msg_timeout (int /*<<< orphan*/ ,int) ; 
 int hdcp2_detect_msg_availability (struct intel_digital_port*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static ssize_t
intel_hdmi_hdcp2_wait_for_msg(struct intel_digital_port *intel_dig_port,
			      u8 msg_id, bool paired)
{
	bool msg_ready = false;
	int timeout, ret;
	ssize_t msg_sz = 0;

	timeout = get_hdcp2_msg_timeout(msg_id, paired);
	if (timeout < 0)
		return timeout;

	ret = __wait_for(ret = hdcp2_detect_msg_availability(intel_dig_port,
							     msg_id, &msg_ready,
							     &msg_sz),
			 !ret && msg_ready && msg_sz, timeout * 1000,
			 1000, 5 * 1000);
	if (ret)
		DRM_DEBUG_KMS("msg_id: %d, ret: %d, timeout: %d\n",
			      msg_id, ret, timeout);

	return ret ? ret : msg_sz;
}