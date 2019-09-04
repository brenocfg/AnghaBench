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
struct rk3x_i2c_calced_timings {unsigned long div_low; unsigned long div_high; int tuning; } ;
struct i2c_timings {int bus_freq_hz; unsigned long scl_rise_ns; unsigned long scl_fall_ns; } ;
struct i2c_spec_values {unsigned long min_high_ns; unsigned long min_low_ns; unsigned long max_data_hold_ns; unsigned long min_data_setup_ns; unsigned long min_setup_start_ns; unsigned long min_setup_stop_ns; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 int EINVAL ; 
 int REG_CON_SDA_CFG (unsigned long) ; 
 int REG_CON_STA_CFG (unsigned long) ; 
 int REG_CON_STO_CFG (unsigned long) ; 
 scalar_t__ WARN_ON (int) ; 
 struct i2c_spec_values* rk3x_i2c_get_spec (int) ; 

__attribute__((used)) static int rk3x_i2c_v1_calc_timings(unsigned long clk_rate,
				    struct i2c_timings *t,
				    struct rk3x_i2c_calced_timings *t_calc)
{
	unsigned long min_low_ns, min_high_ns;
	unsigned long min_setup_start_ns, min_setup_data_ns;
	unsigned long min_setup_stop_ns, max_hold_data_ns;

	unsigned long clk_rate_khz, scl_rate_khz;

	unsigned long min_low_div, min_high_div;

	unsigned long min_div_for_hold, min_total_div;
	unsigned long extra_div, extra_low_div;
	unsigned long sda_update_cfg, stp_sta_cfg, stp_sto_cfg;

	const struct i2c_spec_values *spec;
	int ret = 0;

	/* Support standard-mode, fast-mode and fast-mode plus */
	if (WARN_ON(t->bus_freq_hz > 1000000))
		t->bus_freq_hz = 1000000;

	/* prevent scl_rate_khz from becoming 0 */
	if (WARN_ON(t->bus_freq_hz < 1000))
		t->bus_freq_hz = 1000;

	/*
	 * min_low_ns: The minimum number of ns we need to hold low to
	 *	       meet I2C specification, should include fall time.
	 * min_high_ns: The minimum number of ns we need to hold high to
	 *	        meet I2C specification, should include rise time.
	 */
	spec = rk3x_i2c_get_spec(t->bus_freq_hz);

	/* calculate min-divh and min-divl */
	clk_rate_khz = DIV_ROUND_UP(clk_rate, 1000);
	scl_rate_khz = t->bus_freq_hz / 1000;
	min_total_div = DIV_ROUND_UP(clk_rate_khz, scl_rate_khz * 8);

	min_high_ns = t->scl_rise_ns + spec->min_high_ns;
	min_high_div = DIV_ROUND_UP(clk_rate_khz * min_high_ns, 8 * 1000000);

	min_low_ns = t->scl_fall_ns + spec->min_low_ns;
	min_low_div = DIV_ROUND_UP(clk_rate_khz * min_low_ns, 8 * 1000000);

	/*
	 * Final divh and divl must be greater than 0, otherwise the
	 * hardware would not output the i2c clk.
	 */
	min_high_div = (min_high_div < 1) ? 2 : min_high_div;
	min_low_div = (min_low_div < 1) ? 2 : min_low_div;

	/* These are the min dividers needed for min hold times. */
	min_div_for_hold = (min_low_div + min_high_div);

	/*
	 * This is the maximum divider so we don't go over the maximum.
	 * We don't round up here (we round down) since this is a maximum.
	 */
	if (min_div_for_hold >= min_total_div) {
		/*
		 * Time needed to meet hold requirements is important.
		 * Just use that.
		 */
		t_calc->div_low = min_low_div;
		t_calc->div_high = min_high_div;
	} else {
		/*
		 * We've got to distribute some time among the low and high
		 * so we don't run too fast.
		 * We'll try to split things up by the scale of min_low_div and
		 * min_high_div, biasing slightly towards having a higher div
		 * for low (spend more time low).
		 */
		extra_div = min_total_div - min_div_for_hold;
		extra_low_div = DIV_ROUND_UP(min_low_div * extra_div,
					     min_div_for_hold);

		t_calc->div_low = min_low_div + extra_low_div;
		t_calc->div_high = min_high_div + (extra_div - extra_low_div);
	}

	/*
	 * calculate sda data hold count by the rules, data_upd_st:3
	 * is a appropriate value to reduce calculated times.
	 */
	for (sda_update_cfg = 3; sda_update_cfg > 0; sda_update_cfg--) {
		max_hold_data_ns =  DIV_ROUND_UP((sda_update_cfg
						 * (t_calc->div_low) + 1)
						 * 1000000, clk_rate_khz);
		min_setup_data_ns =  DIV_ROUND_UP(((8 - sda_update_cfg)
						 * (t_calc->div_low) + 1)
						 * 1000000, clk_rate_khz);
		if ((max_hold_data_ns < spec->max_data_hold_ns) &&
		    (min_setup_data_ns > spec->min_data_setup_ns))
			break;
	}

	/* calculate setup start config */
	min_setup_start_ns = t->scl_rise_ns + spec->min_setup_start_ns;
	stp_sta_cfg = DIV_ROUND_UP(clk_rate_khz * min_setup_start_ns
			   - 1000000, 8 * 1000000 * (t_calc->div_high));

	/* calculate setup stop config */
	min_setup_stop_ns = t->scl_rise_ns + spec->min_setup_stop_ns;
	stp_sto_cfg = DIV_ROUND_UP(clk_rate_khz * min_setup_stop_ns
			   - 1000000, 8 * 1000000 * (t_calc->div_high));

	t_calc->tuning = REG_CON_SDA_CFG(--sda_update_cfg) |
			 REG_CON_STA_CFG(--stp_sta_cfg) |
			 REG_CON_STO_CFG(--stp_sto_cfg);

	t_calc->div_low--;
	t_calc->div_high--;

	/* Maximum divider supported by hw is 0xffff */
	if (t_calc->div_low > 0xffff) {
		t_calc->div_low = 0xffff;
		ret = -EINVAL;
	}

	if (t_calc->div_high > 0xffff) {
		t_calc->div_high = 0xffff;
		ret = -EINVAL;
	}

	return ret;
}