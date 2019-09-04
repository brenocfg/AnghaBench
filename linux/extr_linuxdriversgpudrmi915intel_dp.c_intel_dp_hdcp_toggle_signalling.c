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
struct intel_digital_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static
int intel_dp_hdcp_toggle_signalling(struct intel_digital_port *intel_dig_port,
				    bool enable)
{
	/* Not used for single stream DisplayPort setups */
	return 0;
}