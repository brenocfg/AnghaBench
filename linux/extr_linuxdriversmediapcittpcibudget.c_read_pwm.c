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
typedef  int u8 ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct budget {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static u8 read_pwm(struct budget* budget)
{
	u8 b = 0xff;
	u8 pwm;
	struct i2c_msg msg[] = { { .addr = 0x50,.flags = 0,.buf = &b,.len = 1 },
				 { .addr = 0x50,.flags = I2C_M_RD,.buf = &pwm,.len = 1} };

	if ((i2c_transfer(&budget->i2c_adap, msg, 2) != 2) || (pwm == 0xff))
		pwm = 0x48;

	return pwm;
}