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
struct img_i2c {int /*<<< orphan*/  int_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GEN_START ; 
 int /*<<< orphan*/  MODE_ATOMIC ; 
 int /*<<< orphan*/  SCB_INT_MASK_REG ; 
 int /*<<< orphan*/  img_i2c_atomic_op (struct img_i2c*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  img_i2c_switch_mode (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_i2c_atomic_start(struct img_i2c *i2c)
{
	img_i2c_switch_mode(i2c, MODE_ATOMIC);
	img_i2c_writel(i2c, SCB_INT_MASK_REG, i2c->int_enable);
	img_i2c_atomic_op(i2c, CMD_GEN_START, 0x00);
}