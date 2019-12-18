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
 int AUX_ADDRESS_LEN ; 
 int AUX_CMD_LEN ; 
 int AUX_LENGTH_LEN ; 
 int AUX_PRECHARGE_LEN ; 
 int AUX_STOP_LEN ; 
 int AUX_SYNC_LEN ; 
 int DP_AUX_I2C_READ ; 

__attribute__((used)) static int drm_dp_aux_req_duration(const struct drm_dp_aux_msg *msg)
{
	int len = AUX_PRECHARGE_LEN + AUX_SYNC_LEN + AUX_STOP_LEN +
		AUX_CMD_LEN + AUX_ADDRESS_LEN + AUX_LENGTH_LEN;

	if ((msg->request & DP_AUX_I2C_READ) == 0)
		len += msg->size * 8;

	return len;
}