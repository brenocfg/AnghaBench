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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CMDBUF0_ADDR ; 
 int /*<<< orphan*/  REG_CMDWR_ADDRH ; 
 int /*<<< orphan*/  REG_CMDWR_ADDRL ; 
 int /*<<< orphan*/  debug ; 
 int s5k4ecgx_i2c_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int) ; 

__attribute__((used)) static int s5k4ecgx_write(struct i2c_client *client, u32 addr, u16 val)
{
	u16 high = addr >> 16, low = addr & 0xffff;
	int ret;

	v4l2_dbg(3, debug, client, "write: 0x%08x : 0x%04x\n", addr, val);

	ret = s5k4ecgx_i2c_write(client, REG_CMDWR_ADDRH, high);
	if (!ret)
		ret = s5k4ecgx_i2c_write(client, REG_CMDWR_ADDRL, low);
	if (!ret)
		ret = s5k4ecgx_i2c_write(client, REG_CMDBUF0_ADDR, val);

	return ret;
}