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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct i2c_msg {int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int i2c_io(struct i2c_adapter *adapter, u8 adr,
		  u8 *wbuf, u32 wlen, u8 *rbuf, u32 rlen)
{
	struct i2c_msg msgs[2] = {{.addr = adr,  .flags = 0,
				   .buf  = wbuf, .len   = wlen },
				  {.addr = adr,  .flags = I2C_M_RD,
				   .buf  = rbuf,  .len   = rlen } };
	return (i2c_transfer(adapter, msgs, 2) == 2) ? 0 : -1;
}