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
struct i2c_msg {int flags; } ;
struct drm_dp_aux_msg {int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_AUX_I2C_MOT ; 
 int /*<<< orphan*/  DP_AUX_I2C_READ ; 
 int /*<<< orphan*/  DP_AUX_I2C_WRITE ; 
 int I2C_M_RD ; 

__attribute__((used)) static void drm_dp_i2c_msg_set_request(struct drm_dp_aux_msg *msg,
				       const struct i2c_msg *i2c_msg)
{
	msg->request = (i2c_msg->flags & I2C_M_RD) ?
		DP_AUX_I2C_READ : DP_AUX_I2C_WRITE;
	msg->request |= DP_AUX_I2C_MOT;
}