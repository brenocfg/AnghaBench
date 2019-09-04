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
struct drm_dp_aux_msg {int request; int size; } ;

/* Variables and functions */
 int AUX_CMD_LEN ; 
 int AUX_PRECHARGE_LEN ; 
 int AUX_REPLY_PAD_LEN ; 
 int AUX_STOP_LEN ; 
 int AUX_SYNC_LEN ; 
 int DP_AUX_I2C_READ ; 

__attribute__((used)) static int drm_dp_aux_reply_duration(const struct drm_dp_aux_msg *msg)
{
	int len = AUX_PRECHARGE_LEN + AUX_SYNC_LEN + AUX_STOP_LEN +
		AUX_CMD_LEN + AUX_REPLY_PAD_LEN;

	/*
	 * For read we expect what was asked. For writes there will
	 * be 0 or 1 data bytes. Assume 0 for the "best" case.
	 */
	if (msg->request & DP_AUX_I2C_READ)
		len += msg->size * 8;

	return len;
}