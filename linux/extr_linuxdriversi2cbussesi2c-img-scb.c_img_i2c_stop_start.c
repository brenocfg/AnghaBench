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
struct img_i2c {int at_slave_event; int at_t_done; int at_cur_cmd; int /*<<< orphan*/  seq; int /*<<< orphan*/  int_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_SEQUENCE ; 
 int /*<<< orphan*/  SCB_INT_MASK_REG ; 
 int /*<<< orphan*/  img_i2c_sequence (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_stop_seq ; 
 int /*<<< orphan*/  img_i2c_switch_mode (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_i2c_stop_start(struct img_i2c *i2c)
{
	/* Initiate a stop bit sequence */
	img_i2c_switch_mode(i2c, MODE_SEQUENCE);
	img_i2c_writel(i2c, SCB_INT_MASK_REG, i2c->int_enable);
	i2c->seq = img_i2c_stop_seq;
	i2c->at_slave_event = true;
	i2c->at_t_done = true;
	i2c->at_cur_cmd = -1;

	/* img_i2c_stop_seq isn't empty so the following won't fail */
	img_i2c_sequence(i2c, 0);
}