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
typedef  int u8 ;
struct lg216x_state {int dummy; } ;

/* Variables and functions */
 int lg216x_read_reg (struct lg216x_state*,int,int*) ; 
 int lg216x_soft_reset (struct lg216x_state*) ; 
 int lg216x_write_reg (struct lg216x_state*,int,int) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static int lg2160_spectrum_polarity(struct lg216x_state *state,
				    int inverted)
{
	u8 val;
	int ret;

	ret = lg216x_read_reg(state, 0x0132, &val);
	if (lg_fail(ret))
		goto fail;

	val &= 0xfd;
	val |= (inverted) ? 0x02 : 0x00;

	ret = lg216x_write_reg(state, 0x0132, val);
	lg_fail(ret);
fail:
	return lg216x_soft_reset(state);
}