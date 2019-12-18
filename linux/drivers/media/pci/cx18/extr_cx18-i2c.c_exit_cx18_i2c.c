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
struct cx18 {int /*<<< orphan*/ * i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_I2C (char*) ; 
 int /*<<< orphan*/  CX18_REG_I2C_1_WR ; 
 int /*<<< orphan*/  CX18_REG_I2C_2_WR ; 
 int cx18_read_reg (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void exit_cx18_i2c(struct cx18 *cx)
{
	int i;
	CX18_DEBUG_I2C("i2c exit\n");
	cx18_write_reg(cx, cx18_read_reg(cx, CX18_REG_I2C_1_WR) | 4,
							CX18_REG_I2C_1_WR);
	cx18_write_reg(cx, cx18_read_reg(cx, CX18_REG_I2C_2_WR) | 4,
							CX18_REG_I2C_2_WR);

	for (i = 0; i < 2; i++) {
		i2c_del_adapter(&cx->i2c_adap[i]);
	}
}