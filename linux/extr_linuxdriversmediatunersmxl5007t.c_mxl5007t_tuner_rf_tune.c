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
typedef  int /*<<< orphan*/  u32 ;
struct reg_pair_t {int dummy; } ;
struct mxl5007t_state {int dummy; } ;
typedef  enum mxl5007t_bw_mhz { ____Placeholder_mxl5007t_bw_mhz } mxl5007t_bw_mhz ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 struct reg_pair_t* mxl5007t_calc_rf_tune_regs (struct mxl5007t_state*,int /*<<< orphan*/ ,int) ; 
 int mxl5007t_write_regs (struct mxl5007t_state*,struct reg_pair_t*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static int mxl5007t_tuner_rf_tune(struct mxl5007t_state *state, u32 rf_freq_hz,
				  enum mxl5007t_bw_mhz bw)
{
	struct reg_pair_t *rf_tune_regs;
	int ret;

	/* calculate channel change reg array */
	rf_tune_regs = mxl5007t_calc_rf_tune_regs(state, rf_freq_hz, bw);

	ret = mxl5007t_write_regs(state, rf_tune_regs);
	if (mxl_fail(ret))
		goto fail;
	msleep(3);
fail:
	return ret;
}