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
typedef  int /*<<< orphan*/  u32 ;
struct slimpro_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIMPRO_IIC_BUS ; 
 int /*<<< orphan*/  SLIMPRO_IIC_ENCODE_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIMPRO_IIC_ENCODE_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIMPRO_IIC_WRITE ; 
 int slimpro_i2c_send_msg (struct slimpro_i2c_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int slimpro_i2c_wr(struct slimpro_i2c_dev *ctx, u32 chip,
			  u32 addr, u32 addrlen, u32 protocol, u32 writelen,
			  u32 data)
{
	u32 msg[3];

	msg[0] = SLIMPRO_IIC_ENCODE_MSG(SLIMPRO_IIC_BUS, chip,
					SLIMPRO_IIC_WRITE, protocol, addrlen, writelen);
	msg[1] = SLIMPRO_IIC_ENCODE_ADDR(addr);
	msg[2] = data;

	return slimpro_i2c_send_msg(ctx, msg, msg);
}