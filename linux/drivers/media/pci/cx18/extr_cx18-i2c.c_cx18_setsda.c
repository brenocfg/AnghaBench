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
struct cx18_i2c_algo_callback_data {int bus_index; struct cx18* cx; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int CX18_REG_I2C_1_WR ; 
 int CX18_REG_I2C_2_WR ; 
 int SETSDL_BIT ; 
 int cx18_read_reg (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int) ; 

__attribute__((used)) static void cx18_setsda(void *data, int state)
{
	struct cx18 *cx = ((struct cx18_i2c_algo_callback_data *)data)->cx;
	int bus_index = ((struct cx18_i2c_algo_callback_data *)data)->bus_index;
	u32 addr = bus_index ? CX18_REG_I2C_2_WR : CX18_REG_I2C_1_WR;
	u32 r = cx18_read_reg(cx, addr);

	if (state)
		cx18_write_reg(cx, r | SETSDL_BIT, addr);
	else
		cx18_write_reg(cx, r & ~SETSDL_BIT, addr);
}