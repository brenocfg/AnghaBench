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
 int DP_BCAPS_HDCP_CAPABLE ; 
 int intel_dp_hdcp_read_bcaps (struct intel_digital_port*,int*) ; 

__attribute__((used)) static
int intel_dp_hdcp_capable(struct intel_digital_port *intel_dig_port,
			  bool *hdcp_capable)
{
	ssize_t ret;
	u8 bcaps;

	ret = intel_dp_hdcp_read_bcaps(intel_dig_port, &bcaps);
	if (ret)
		return ret;

	*hdcp_capable = bcaps & DP_BCAPS_HDCP_CAPABLE;
	return 0;
}