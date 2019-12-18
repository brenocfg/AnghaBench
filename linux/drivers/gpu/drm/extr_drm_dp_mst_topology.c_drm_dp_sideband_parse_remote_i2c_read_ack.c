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
struct drm_dp_sideband_msg_rx {int* msg; int curlen; } ;
struct TYPE_4__ {int port_number; int num_bytes; int /*<<< orphan*/  bytes; } ;
struct TYPE_3__ {TYPE_2__ remote_i2c_read_ack; } ;
struct drm_dp_sideband_msg_reply_body {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static bool drm_dp_sideband_parse_remote_i2c_read_ack(struct drm_dp_sideband_msg_rx *raw,
						      struct drm_dp_sideband_msg_reply_body *repmsg)
{
	int idx = 1;

	repmsg->u.remote_i2c_read_ack.port_number = (raw->msg[idx] & 0xf);
	idx++;
	if (idx > raw->curlen)
		goto fail_len;
	repmsg->u.remote_i2c_read_ack.num_bytes = raw->msg[idx];
	idx++;
	/* TODO check */
	memcpy(repmsg->u.remote_i2c_read_ack.bytes, &raw->msg[idx], repmsg->u.remote_i2c_read_ack.num_bytes);
	return true;
fail_len:
	DRM_DEBUG_KMS("remote i2c reply parse length fail %d %d\n", idx, raw->curlen);
	return false;
}