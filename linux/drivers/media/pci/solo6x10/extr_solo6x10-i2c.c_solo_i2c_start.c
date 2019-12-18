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
typedef  int u32 ;
struct solo_dev {int /*<<< orphan*/  i2c_state; TYPE_1__* i2c_msg; } ;
struct TYPE_2__ {int addr; int flags; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int /*<<< orphan*/  IIC_STATE_START ; 
 int /*<<< orphan*/  SOLO_IIC_TXD ; 
 int /*<<< orphan*/  solo_i2c_flush (struct solo_dev*,int) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void solo_i2c_start(struct solo_dev *solo_dev)
{
	u32 addr = solo_dev->i2c_msg->addr << 1;

	if (solo_dev->i2c_msg->flags & I2C_M_RD)
		addr |= 1;

	solo_dev->i2c_state = IIC_STATE_START;
	solo_reg_write(solo_dev, SOLO_IIC_TXD, addr);
	solo_i2c_flush(solo_dev, 1);
}