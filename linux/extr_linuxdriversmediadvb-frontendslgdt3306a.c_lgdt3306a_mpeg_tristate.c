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
struct lgdt3306a_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 scalar_t__ lg_chkerr (int) ; 
 int lgdt3306a_read_reg (struct lgdt3306a_state*,int,int*) ; 
 int lgdt3306a_set_reg_bit (struct lgdt3306a_state*,int,int,int) ; 
 int lgdt3306a_write_reg (struct lgdt3306a_state*,int,int) ; 

__attribute__((used)) static int lgdt3306a_mpeg_tristate(struct lgdt3306a_state *state,
				     int mode)
{
	u8 val;
	int ret;

	dbg_info("(%d)\n", mode);

	if (mode) {
		ret = lgdt3306a_read_reg(state, 0x0070, &val);
		if (lg_chkerr(ret))
			goto fail;
		/*
		 * Tristate bus; TPOUTEN=0x80, TPCLKOUTEN=0x20,
		 * TPDATAOUTEN=0x08
		 */
		val &= ~0xa8;
		ret = lgdt3306a_write_reg(state, 0x0070, val);
		if (lg_chkerr(ret))
			goto fail;

		/* AGCIFOUTENB=0x40; 1=Disable IFAGC pin */
		ret = lgdt3306a_set_reg_bit(state, 0x0003, 6, 1);
		if (lg_chkerr(ret))
			goto fail;

	} else {
		/* enable IFAGC pin */
		ret = lgdt3306a_set_reg_bit(state, 0x0003, 6, 0);
		if (lg_chkerr(ret))
			goto fail;

		ret = lgdt3306a_read_reg(state, 0x0070, &val);
		if (lg_chkerr(ret))
			goto fail;

		val |= 0xa8; /* enable bus */
		ret = lgdt3306a_write_reg(state, 0x0070, val);
		if (lg_chkerr(ret))
			goto fail;
	}

fail:
	return ret;
}