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
struct lgdt3306a_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 scalar_t__ lg_chkerr (int) ; 
 int /*<<< orphan*/  lgdt3306a_DumpAllRegs (struct lgdt3306a_state*) ; 
 int lgdt3306a_set_reg_bit (struct lgdt3306a_state*,int,int,int) ; 

__attribute__((used)) static int lgdt3306a_power(struct lgdt3306a_state *state,
				     int mode)
{
	int ret;

	dbg_info("(%d)\n", mode);

	if (mode == 0) {
		/* into reset */
		ret = lgdt3306a_set_reg_bit(state, 0x0000, 7, 0);
		if (lg_chkerr(ret))
			goto fail;

		/* power down */
		ret = lgdt3306a_set_reg_bit(state, 0x0000, 0, 0);
		if (lg_chkerr(ret))
			goto fail;

	} else {
		/* out of reset */
		ret = lgdt3306a_set_reg_bit(state, 0x0000, 7, 1);
		if (lg_chkerr(ret))
			goto fail;

		/* power up */
		ret = lgdt3306a_set_reg_bit(state, 0x0000, 0, 1);
		if (lg_chkerr(ret))
			goto fail;
	}

#ifdef DBG_DUMP
	lgdt3306a_DumpAllRegs(state);
#endif
fail:
	return ret;
}