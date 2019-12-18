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
typedef  enum atscmh_rs_code_mode { ____Placeholder_atscmh_rs_code_mode } atscmh_rs_code_mode ;
struct TYPE_2__ {int lg_chip; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LG2160 129 
#define  LG2161 128 
 int lg216x_read_reg (struct lg216x_state*,int,int*) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static int lg216x_get_rs_code_mode(struct lg216x_state *state,
				   enum atscmh_rs_code_mode *rs_code_pri,
				   enum atscmh_rs_code_mode *rs_code_sec)
{
	u8 val;
	int ret;

	switch (state->cfg->lg_chip) {
	case LG2160:
		ret = lg216x_read_reg(state, 0x0410, &val);
		break;
	case LG2161:
		ret = lg216x_read_reg(state, 0x0513, &val);
		break;
	default:
		ret = -EINVAL;
	}
	if (lg_fail(ret))
		goto fail;

	*rs_code_pri = (enum atscmh_rs_code_mode) ((val >> 2) & 0x03);
	*rs_code_sec = (enum atscmh_rs_code_mode) (val & 0x03);
fail:
	return ret;
}