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
struct dc_i2c {int /*<<< orphan*/  done; scalar_t__ last; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  II_CMD_STOP ; 
 int /*<<< orphan*/  STATE_STOP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dc_i2c_cmd (struct dc_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dc_i2c_stop(struct dc_i2c *i2c)
{
	i2c->state = STATE_STOP;
	if (i2c->last)
		dc_i2c_cmd(i2c, II_CMD_STOP);
	else
		complete(&i2c->done);
}