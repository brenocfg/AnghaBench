#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct lg216x_state {TYPE_1__* cfg; } ;
struct TYPE_2__ {int output_if; } ;

/* Variables and functions */
 int lg216x_read_reg (struct lg216x_state*,int,int*) ; 
 int lg216x_write_reg (struct lg216x_state*,int,int) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static int lg2161_set_output_interface(struct lg216x_state *state)
{
	u8 val;
	int ret;

	ret = lg216x_read_reg(state, 0x0014, &val);
	if (lg_fail(ret))
		goto fail;

	val &= ~0x07;
	val |= state->cfg->output_if; /* FIXME: needs sanity check */

	ret = lg216x_write_reg(state, 0x0014, val);
	lg_fail(ret);
fail:
	return ret;
}