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
struct intel_connector {int dummy; } ;

/* Variables and functions */
 int hdcp2_authenticate_repeater_topology (struct intel_connector*) ; 
 int hdcp2_propagate_stream_management_info (struct intel_connector*) ; 

__attribute__((used)) static int hdcp2_authenticate_repeater(struct intel_connector *connector)
{
	int ret;

	ret = hdcp2_authenticate_repeater_topology(connector);
	if (ret < 0)
		return ret;

	return hdcp2_propagate_stream_management_info(connector);
}