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
typedef  enum atscmh_rs_frame_ensemble { ____Placeholder_atscmh_rs_frame_ensemble } atscmh_rs_frame_ensemble ;
struct TYPE_2__ {int lg_chip; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LG2160 129 
#define  LG2161 128 
 int lg216x_read_reg (struct lg216x_state*,int,int*) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static
int lg216x_get_rs_frame_ensemble(struct lg216x_state *state,
				 enum atscmh_rs_frame_ensemble *rs_frame_ens)
{
	u8 val;
	int ret;

	switch (state->cfg->lg_chip) {
	case LG2160:
		ret = lg216x_read_reg(state, 0x0400, &val);
		break;
	case LG2161:
		ret = lg216x_read_reg(state, 0x0500, &val);
		break;
	default:
		ret = -EINVAL;
	}
	if (lg_fail(ret))
		goto fail;

	val &= 0x01;
	*rs_frame_ens = (enum atscmh_rs_frame_ensemble) val;
fail:
	return ret;
}