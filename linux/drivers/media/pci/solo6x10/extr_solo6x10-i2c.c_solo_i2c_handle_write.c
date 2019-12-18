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
struct solo_dev {size_t i2c_msg_ptr; scalar_t__ i2c_msg_num; TYPE_1__* i2c_msg; } ;
struct TYPE_2__ {size_t len; int flags; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int I2C_M_NOSTART ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  SOLO_IIC_TXD ; 
 int /*<<< orphan*/  solo_i2c_flush (struct solo_dev*,int) ; 
 int /*<<< orphan*/  solo_i2c_start (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_i2c_stop (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int solo_i2c_handle_write(struct solo_dev *solo_dev)
{
retry_write:
	if (solo_dev->i2c_msg_ptr != solo_dev->i2c_msg->len) {
		solo_reg_write(solo_dev, SOLO_IIC_TXD,
			       solo_dev->i2c_msg->buf[solo_dev->i2c_msg_ptr]);
		solo_dev->i2c_msg_ptr++;
		solo_i2c_flush(solo_dev, 1);
		return 0;
	}

	solo_dev->i2c_msg_ptr = 0;
	solo_dev->i2c_msg++;
	solo_dev->i2c_msg_num--;

	if (solo_dev->i2c_msg_num == 0) {
		solo_i2c_stop(solo_dev);
		return 0;
	}

	if (!(solo_dev->i2c_msg->flags & I2C_M_NOSTART)) {
		solo_i2c_start(solo_dev);
	} else {
		if (solo_dev->i2c_msg->flags & I2C_M_RD)
			solo_i2c_stop(solo_dev);
		else
			goto retry_write;
	}

	return 0;
}