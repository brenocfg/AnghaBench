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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  void* u8 ;
struct drm_dp_sideband_msg_tx {int path_msg; } ;
struct TYPE_3__ {int port_number; int /*<<< orphan*/  sdp_stream_sink; void* number_sdp_streams; int /*<<< orphan*/  pbn; void* vcpi; } ;
struct TYPE_4__ {TYPE_1__ allocate_payload; } ;
struct drm_dp_sideband_msg_req_body {TYPE_2__ u; int /*<<< orphan*/  req_type; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ALLOCATE_PAYLOAD ; 
 int /*<<< orphan*/  drm_dp_encode_sideband_req (struct drm_dp_sideband_msg_req_body*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,void*) ; 
 int /*<<< orphan*/  memset (struct drm_dp_sideband_msg_req_body*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int build_allocate_payload(struct drm_dp_sideband_msg_tx *msg, int port_num,
				  u8 vcpi, uint16_t pbn,
				  u8 number_sdp_streams,
				  u8 *sdp_stream_sink)
{
	struct drm_dp_sideband_msg_req_body req;
	memset(&req, 0, sizeof(req));
	req.req_type = DP_ALLOCATE_PAYLOAD;
	req.u.allocate_payload.port_number = port_num;
	req.u.allocate_payload.vcpi = vcpi;
	req.u.allocate_payload.pbn = pbn;
	req.u.allocate_payload.number_sdp_streams = number_sdp_streams;
	memcpy(req.u.allocate_payload.sdp_stream_sink, sdp_stream_sink,
		   number_sdp_streams);
	drm_dp_encode_sideband_req(&req, msg);
	msg->path_msg = true;
	return 0;
}