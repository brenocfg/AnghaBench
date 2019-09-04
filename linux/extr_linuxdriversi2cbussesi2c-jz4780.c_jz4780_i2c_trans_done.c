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
struct jz4780_i2c {int /*<<< orphan*/  trans_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ4780_I2C_INTM ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz4780_i2c_writew (struct jz4780_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz4780_i2c_trans_done(struct jz4780_i2c *i2c)
{
	jz4780_i2c_writew(i2c, JZ4780_I2C_INTM, 0);
	complete(&i2c->trans_waitq);
}