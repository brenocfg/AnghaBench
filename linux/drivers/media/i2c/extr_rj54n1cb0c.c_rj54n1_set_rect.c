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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rj54n1_set_rect(struct i2c_client *client,
			   u16 reg_x, u16 reg_y, u16 reg_xy,
			   u32 width, u32 height)
{
	int ret;

	ret = reg_write(client, reg_xy,
			((width >> 4) & 0x70) |
			((height >> 8) & 7));

	if (!ret)
		ret = reg_write(client, reg_x, width & 0xff);
	if (!ret)
		ret = reg_write(client, reg_y, height & 0xff);

	return ret;
}