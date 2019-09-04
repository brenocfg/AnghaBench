#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int msg_num; int cmd; scalar_t__ addr_width; scalar_t__ data_len; struct i2c_msg* msg; } ;
struct mlxcpld_i2c_priv {TYPE_1__ xfer; } ;
struct i2c_msg {int flags; scalar_t__ len; } ;

/* Variables and functions */
 int I2C_M_RD ; 

__attribute__((used)) static void mlxcpld_i2c_set_transf_data(struct mlxcpld_i2c_priv *priv,
					struct i2c_msg *msgs, int num,
					u8 comm_len)
{
	priv->xfer.msg = msgs;
	priv->xfer.msg_num = num;

	/*
	 * All upper layers currently are never use transfer with more than
	 * 2 messages. Actually, it's also not so relevant in Mellanox systems
	 * because of HW limitation. Max size of transfer is not more than 32
	 * or 68 bytes in the current x86 LPCI2C bridge.
	 */
	priv->xfer.cmd = msgs[num - 1].flags & I2C_M_RD;

	if (priv->xfer.cmd == I2C_M_RD && comm_len != msgs[0].len) {
		priv->xfer.addr_width = msgs[0].len;
		priv->xfer.data_len = comm_len - priv->xfer.addr_width;
	} else {
		priv->xfer.addr_width = 0;
		priv->xfer.data_len = comm_len;
	}
}