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
typedef  int /*<<< orphan*/  u32 ;
struct solo_dev {scalar_t__ i2c_state; scalar_t__ i2c_msg_ptr; TYPE_1__* i2c_msg; int /*<<< orphan*/  i2c_id; } ;
struct TYPE_2__ {int flags; scalar_t__ len; } ;

/* Variables and functions */
 int I2C_M_NO_RD_ACK ; 
 scalar_t__ IIC_STATE_START ; 
 int /*<<< orphan*/  SOLO_IIC_ACK_EN ; 
 int /*<<< orphan*/  SOLO_IIC_CH_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLO_IIC_CTRL ; 
 int /*<<< orphan*/  SOLO_IIC_READ ; 
 int /*<<< orphan*/  SOLO_IIC_START ; 
 int /*<<< orphan*/  SOLO_IIC_STOP ; 
 int /*<<< orphan*/  SOLO_IIC_WRITE ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_i2c_flush(struct solo_dev *solo_dev, int wr)
{
	u32 ctrl;

	ctrl = SOLO_IIC_CH_SET(solo_dev->i2c_id);

	if (solo_dev->i2c_state == IIC_STATE_START)
		ctrl |= SOLO_IIC_START;

	if (wr) {
		ctrl |= SOLO_IIC_WRITE;
	} else {
		ctrl |= SOLO_IIC_READ;
		if (!(solo_dev->i2c_msg->flags & I2C_M_NO_RD_ACK))
			ctrl |= SOLO_IIC_ACK_EN;
	}

	if (solo_dev->i2c_msg_ptr == solo_dev->i2c_msg->len)
		ctrl |= SOLO_IIC_STOP;

	solo_reg_write(solo_dev, SOLO_IIC_CTRL, ctrl);
}