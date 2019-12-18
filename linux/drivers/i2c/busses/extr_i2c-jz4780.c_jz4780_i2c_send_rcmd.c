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
struct jz4780_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ4780_I2C_DC ; 
 int /*<<< orphan*/  JZ4780_I2C_DC_READ ; 
 int /*<<< orphan*/  jz4780_i2c_writew (struct jz4780_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz4780_i2c_send_rcmd(struct jz4780_i2c *i2c, int cmd_count)
{
	int i;

	for (i = 0; i < cmd_count; i++)
		jz4780_i2c_writew(i2c, JZ4780_I2C_DC, JZ4780_I2C_DC_READ);
}