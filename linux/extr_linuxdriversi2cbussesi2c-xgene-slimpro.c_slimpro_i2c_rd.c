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
typedef  scalar_t__ u32 ;
struct slimpro_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIMPRO_IIC_BUS ; 
 scalar_t__ SLIMPRO_IIC_ENCODE_ADDR (scalar_t__) ; 
 scalar_t__ SLIMPRO_IIC_ENCODE_MSG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SLIMPRO_IIC_READ ; 
 int slimpro_i2c_send_msg (struct slimpro_i2c_dev*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int slimpro_i2c_rd(struct slimpro_i2c_dev *ctx, u32 chip,
			  u32 addr, u32 addrlen, u32 protocol,
			  u32 readlen, u32 *data)
{
	u32 msg[3];

	msg[0] = SLIMPRO_IIC_ENCODE_MSG(SLIMPRO_IIC_BUS, chip,
					SLIMPRO_IIC_READ, protocol, addrlen, readlen);
	msg[1] = SLIMPRO_IIC_ENCODE_ADDR(addr);
	msg[2] = 0;

	return slimpro_i2c_send_msg(ctx, msg, data);
}