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
struct lgdt3306a_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_reg (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ lg_chkerr (int) ; 
 int lgdt3306a_read_reg (struct lgdt3306a_state*,int /*<<< orphan*/ ,int*) ; 
 int lgdt3306a_write_reg (struct lgdt3306a_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lgdt3306a_set_reg_bit(struct lgdt3306a_state *state,
				u16 reg, int bit, int onoff)
{
	u8 val;
	int ret;

	dbg_reg("reg: 0x%04x, bit: %d, level: %d\n", reg, bit, onoff);

	ret = lgdt3306a_read_reg(state, reg, &val);
	if (lg_chkerr(ret))
		goto fail;

	val &= ~(1 << bit);
	val |= (onoff & 1) << bit;

	ret = lgdt3306a_write_reg(state, reg, val);
	lg_chkerr(ret);
fail:
	return ret;
}