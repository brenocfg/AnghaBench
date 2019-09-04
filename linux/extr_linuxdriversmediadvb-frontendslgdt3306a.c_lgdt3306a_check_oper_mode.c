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
typedef  enum lgdt3306a_modulation { ____Placeholder_lgdt3306a_modulation } lgdt3306a_modulation ;

/* Variables and functions */
 int LG3306_QAM256 ; 
 int LG3306_QAM64 ; 
 int LG3306_UNKNOWN_MODE ; 
 int LG3306_VSB ; 
 int /*<<< orphan*/  dbg_info (char*) ; 
 int lgdt3306a_read_reg (struct lgdt3306a_state*,int,int*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static enum lgdt3306a_modulation
lgdt3306a_check_oper_mode(struct lgdt3306a_state *state)
{
	u8 val = 0;
	int ret;

	ret = lgdt3306a_read_reg(state, 0x0081, &val);
	if (ret)
		goto err;

	if (val & 0x80)	{
		dbg_info("VSB\n");
		return LG3306_VSB;
	}
	if (val & 0x08) {
		ret = lgdt3306a_read_reg(state, 0x00a6, &val);
		if (ret)
			goto err;
		val = val >> 2;
		if (val & 0x01) {
			dbg_info("QAM256\n");
			return LG3306_QAM256;
		}
		dbg_info("QAM64\n");
		return LG3306_QAM64;
	}
err:
	pr_warn("UNKNOWN\n");
	return LG3306_UNKNOWN_MODE;
}