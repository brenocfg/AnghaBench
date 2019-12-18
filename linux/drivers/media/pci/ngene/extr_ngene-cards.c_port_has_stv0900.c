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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ i2c_read_reg16 (struct i2c_adapter*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int port_has_stv0900(struct i2c_adapter *i2c, int port)
{
	u8 val;
	if (i2c_read_reg16(i2c, 0x68+port/2, 0xf100, &val) < 0)
		return 0;
	return 1;
}