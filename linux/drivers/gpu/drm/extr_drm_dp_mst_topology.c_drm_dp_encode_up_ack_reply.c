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
struct drm_dp_sideband_msg_tx {int dummy; } ;
struct drm_dp_sideband_msg_reply_body {int /*<<< orphan*/  req_type; int /*<<< orphan*/  reply_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SIDEBAND_REPLY_ACK ; 
 int /*<<< orphan*/  drm_dp_encode_sideband_reply (struct drm_dp_sideband_msg_reply_body*,struct drm_dp_sideband_msg_tx*) ; 

__attribute__((used)) static int drm_dp_encode_up_ack_reply(struct drm_dp_sideband_msg_tx *msg, u8 req_type)
{
	struct drm_dp_sideband_msg_reply_body reply;

	reply.reply_type = DP_SIDEBAND_REPLY_ACK;
	reply.req_type = req_type;
	drm_dp_encode_sideband_reply(&reply, msg);
	return 0;
}