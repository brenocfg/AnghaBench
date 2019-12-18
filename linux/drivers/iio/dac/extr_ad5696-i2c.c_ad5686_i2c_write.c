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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct i2c_client {int dummy; } ;
struct ad5686_state {TYPE_1__* data; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * d8; int /*<<< orphan*/  d32; } ;

/* Variables and functions */
 int AD5686_ADDR (int /*<<< orphan*/ ) ; 
 int AD5686_CMD (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5686_i2c_write(struct ad5686_state *st,
			    u8 cmd, u8 addr, u16 val)
{
	struct i2c_client *i2c = to_i2c_client(st->dev);
	int ret;

	st->data[0].d32 = cpu_to_be32(AD5686_CMD(cmd) | AD5686_ADDR(addr)
				      | val);

	ret = i2c_master_send(i2c, &st->data[0].d8[1], 3);
	if (ret < 0)
		return ret;

	return (ret != 3) ? -EIO : 0;
}