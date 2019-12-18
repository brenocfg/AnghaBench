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
typedef  int /*<<< orphan*/  u32 ;
struct img_i2c {int /*<<< orphan*/  at_cur_data; int /*<<< orphan*/  at_cur_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_ATOMIC ; 
 int /*<<< orphan*/  img_i2c_atomic_op (struct img_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_switch_mode (struct img_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int img_i2c_raw_atomic_delay_handler(struct img_i2c *i2c,
					u32 int_status, u32 line_status)
{
	/* Stay in raw mode for this, so we don't just loop infinitely */
	img_i2c_atomic_op(i2c, i2c->at_cur_cmd, i2c->at_cur_data);
	img_i2c_switch_mode(i2c, MODE_ATOMIC);
	return 0;
}