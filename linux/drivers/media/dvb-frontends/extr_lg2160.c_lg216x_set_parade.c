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
struct lg216x_state {int parade_id; } ;

/* Variables and functions */
 int lg216x_write_reg (struct lg216x_state*,int,int) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static int lg216x_set_parade(struct lg216x_state *state, int id)
{
	int ret;

	ret = lg216x_write_reg(state, 0x013e, id & 0x7f);
	if (lg_fail(ret))
		goto fail;

	state->parade_id = id & 0x7f;
fail:
	return ret;
}