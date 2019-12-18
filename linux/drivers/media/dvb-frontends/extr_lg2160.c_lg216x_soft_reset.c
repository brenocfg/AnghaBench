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
struct lg216x_state {int /*<<< orphan*/  last_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int lg216x_write_reg (struct lg216x_state*,int,int) ; 
 int /*<<< orphan*/  lg_dbg (char*) ; 
 scalar_t__ lg_fail (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lg216x_soft_reset(struct lg216x_state *state)
{
	int ret;

	lg_dbg("\n");

	ret = lg216x_write_reg(state, 0x0002, 0x00);
	if (lg_fail(ret))
		goto fail;

	msleep(20);
	ret = lg216x_write_reg(state, 0x0002, 0x01);
	if (lg_fail(ret))
		goto fail;

	state->last_reset = jiffies_to_msecs(jiffies);
fail:
	return ret;
}