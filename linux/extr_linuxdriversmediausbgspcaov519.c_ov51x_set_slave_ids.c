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
typedef  scalar_t__ u8 ;
struct sd {int bridge; scalar_t__ sensor_addr; } ;

/* Variables and functions */
#define  BRIDGE_OVFX2 129 
#define  BRIDGE_W9968CF 128 
 int /*<<< orphan*/  OVFX2_I2C_ADDR ; 
 int /*<<< orphan*/  R51x_I2C_R_SID ; 
 int /*<<< orphan*/  R51x_I2C_W_SID ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ov51x_set_slave_ids(struct sd *sd,
				u8 slave)
{
	switch (sd->bridge) {
	case BRIDGE_OVFX2:
		reg_w(sd, OVFX2_I2C_ADDR, slave);
		return;
	case BRIDGE_W9968CF:
		sd->sensor_addr = slave;
		return;
	}

	reg_w(sd, R51x_I2C_W_SID, slave);
	reg_w(sd, R51x_I2C_R_SID, slave + 1);
}