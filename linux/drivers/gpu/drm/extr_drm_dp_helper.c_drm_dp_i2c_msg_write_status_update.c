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
struct drm_dp_aux_msg {int request; } ;

/* Variables and functions */
 int DP_AUX_I2C_MOT ; 
 int DP_AUX_I2C_WRITE ; 
 int DP_AUX_I2C_WRITE_STATUS_UPDATE ; 

__attribute__((used)) static void drm_dp_i2c_msg_write_status_update(struct drm_dp_aux_msg *msg)
{
	/*
	 * In case of i2c defer or short i2c ack reply to a write,
	 * we need to switch to WRITE_STATUS_UPDATE to drain the
	 * rest of the message
	 */
	if ((msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_I2C_WRITE) {
		msg->request &= DP_AUX_I2C_MOT;
		msg->request |= DP_AUX_I2C_WRITE_STATUS_UPDATE;
	}
}