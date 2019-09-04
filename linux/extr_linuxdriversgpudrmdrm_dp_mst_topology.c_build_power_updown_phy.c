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
struct drm_dp_sideband_msg_tx {int path_msg; } ;
struct TYPE_3__ {int port_number; } ;
struct TYPE_4__ {TYPE_1__ port_num; } ;
struct drm_dp_sideband_msg_req_body {TYPE_2__ u; int /*<<< orphan*/  req_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_POWER_DOWN_PHY ; 
 int /*<<< orphan*/  DP_POWER_UP_PHY ; 
 int /*<<< orphan*/  drm_dp_encode_sideband_req (struct drm_dp_sideband_msg_req_body*,struct drm_dp_sideband_msg_tx*) ; 

__attribute__((used)) static int build_power_updown_phy(struct drm_dp_sideband_msg_tx *msg,
				  int port_num, bool power_up)
{
	struct drm_dp_sideband_msg_req_body req;

	if (power_up)
		req.req_type = DP_POWER_UP_PHY;
	else
		req.req_type = DP_POWER_DOWN_PHY;

	req.u.port_num.port_number = port_num;
	drm_dp_encode_sideband_req(&req, msg);
	msg->path_msg = true;
	return 0;
}