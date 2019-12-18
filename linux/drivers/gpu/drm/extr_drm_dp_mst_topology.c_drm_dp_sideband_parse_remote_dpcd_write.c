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
struct TYPE_3__ {int port_number; } ;
struct TYPE_4__ {TYPE_1__ remote_dpcd_write_ack; } ;
struct drm_dp_sideband_msg_reply_body {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 

__attribute__((used)) static bool drm_dp_sideband_parse_remote_dpcd_write(struct drm_dp_sideband_msg_rx *raw,
						      struct drm_dp_sideband_msg_reply_body *repmsg)
{
	int idx = 1;
	repmsg->u.remote_dpcd_write_ack.port_number = raw->msg[idx] & 0xf;
	idx++;
	if (idx > raw->curlen)
		goto fail_len;
	return true;
fail_len:
	DRM_DEBUG_KMS("parse length fail %d %d\n", idx, raw->curlen);
	return false;
}