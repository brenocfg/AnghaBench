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
typedef  int /*<<< orphan*/  u16 ;
struct lg216x_state {int dummy; } ;

/* Variables and functions */
 int lg216x_read_reg (struct lg216x_state*,int /*<<< orphan*/ ,int*) ; 
 int lg216x_write_reg (struct lg216x_state*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lg_fail (int) ; 
 int /*<<< orphan*/  lg_reg (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lg216x_set_reg_bit(struct lg216x_state *state,
			      u16 reg, int bit, int onoff)
{
	u8 val;
	int ret;

	lg_reg("reg: 0x%04x, bit: %d, level: %d\n", reg, bit, onoff);

	ret = lg216x_read_reg(state, reg, &val);
	if (lg_fail(ret))
		goto fail;

	val &= ~(1 << bit);
	val |= (onoff & 1) << bit;

	ret = lg216x_write_reg(state, reg, val);
	lg_fail(ret);
fail:
	return ret;
}