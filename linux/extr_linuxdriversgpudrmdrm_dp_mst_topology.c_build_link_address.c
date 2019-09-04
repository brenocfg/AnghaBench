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
struct drm_dp_sideband_msg_tx {int dummy; } ;
struct drm_dp_sideband_msg_req_body {int /*<<< orphan*/  req_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_LINK_ADDRESS ; 
 int /*<<< orphan*/  drm_dp_encode_sideband_req (struct drm_dp_sideband_msg_req_body*,struct drm_dp_sideband_msg_tx*) ; 

__attribute__((used)) static int build_link_address(struct drm_dp_sideband_msg_tx *msg)
{
	struct drm_dp_sideband_msg_req_body req;

	req.req_type = DP_LINK_ADDRESS;
	drm_dp_encode_sideband_req(&req, msg);
	return 0;
}