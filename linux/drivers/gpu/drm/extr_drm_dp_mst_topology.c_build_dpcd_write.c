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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_dp_sideband_msg_tx {int dummy; } ;
struct TYPE_4__ {void** bytes; void* num_bytes; int /*<<< orphan*/  dpcd_address; void* port_number; } ;
struct TYPE_3__ {TYPE_2__ dpcd_write; } ;
struct drm_dp_sideband_msg_req_body {TYPE_1__ u; int /*<<< orphan*/  req_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_REMOTE_DPCD_WRITE ; 
 int /*<<< orphan*/  drm_dp_encode_sideband_req (struct drm_dp_sideband_msg_req_body*,struct drm_dp_sideband_msg_tx*) ; 

__attribute__((used)) static int build_dpcd_write(struct drm_dp_sideband_msg_tx *msg, u8 port_num, u32 offset, u8 num_bytes, u8 *bytes)
{
	struct drm_dp_sideband_msg_req_body req;

	req.req_type = DP_REMOTE_DPCD_WRITE;
	req.u.dpcd_write.port_number = port_num;
	req.u.dpcd_write.dpcd_address = offset;
	req.u.dpcd_write.num_bytes = num_bytes;
	req.u.dpcd_write.bytes = bytes;
	drm_dp_encode_sideband_req(&req, msg);

	return 0;
}