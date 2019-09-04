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
struct rk3x_i2c_calced_timings {unsigned long div_low; unsigned long div_high; scalar_t__ tuning; } ;
struct i2c_timings {int bus_freq_hz; unsigned long scl_rise_ns; unsigned long sda_fall_ns; unsigned long scl_fall_ns; } ;
struct i2c_spec_values {unsigned long min_high_ns; int min_setup_start_ns; unsigned long min_low_ns; int max_data_hold_ns; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned long,unsigned long) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 struct i2c_spec_values* rk3x_i2c_get_spec (int) ; 

__attribute__((used)) static int rk3x_i2c_v0_calc_timings(unsigned long clk_rate,
				    struct i2c_timings *t,
				    struct rk3x_i2c_calced_timings *t_calc)
{
	unsigned long min_low_ns, min_high_ns;
	unsigned long max_low_ns, min_total_ns;

	unsigned long clk_rate_khz, scl_rate_khz;

	unsigned long min_low_div, min_high_div;
	unsigned long max_low_div;

	unsigned long min_div_for_hold, min_total_div;
	unsigned long extra_div, extra_low_div, ideal_low_div;

	unsigned long data_hold_buffer_ns = 50;
	const struct i2c_spec_values *spec;
	int ret = 0;

	/* Only support standard-mode and fast-mode */
	if (WARN_ON(t->bus_freq_hz > 400000))
		t->bus_freq_hz = 400000;

	/* prevent scl_rate_khz from becoming 0 */
	if (WARN_ON(t->bus_freq_hz < 1000))
		t->bus_freq_hz = 1000;

	/*
	 * min_low_ns:  The minimum number of ns we need to hold low to
	 *		meet I2C specification, should include fall time.
	 * min_high_ns: The minimum number of ns we need to hold high to
	 *		meet I2C specification, should include rise time.
	 * max_low_ns:  The maximum number of ns we can hold low to meet
	 *		I2C specification.
	 *
	 * Note: max_low_ns should be (maximum data hold time * 2 - buffer)
	 *	 This is because the i2c host on Rockchip holds the data line
	 *	 for half the low time.
	 */
	spec = rk3x_i2c_get_spec(t->bus_freq_hz);
	min_high_ns = t->scl_rise_ns + spec->min_high_ns;

	/*
	 * Timings for repeated start:
	 * - controller appears to drop SDA at .875x (7/8) programmed clk high.
	 * - controller appears to keep SCL high for 2x programmed clk high.
	 *
	 * We need to account for those rules in picking our "high" time so
	 * we meet tSU;STA and tHD;STA times.
	 */
	min_high_ns = max(min_high_ns, DIV_ROUND_UP(
		(t->scl_rise_ns + spec->min_setup_start_ns) * 1000, 875));
	min_high_ns = max(min_high_ns, DIV_ROUND_UP(
		(t->scl_rise_ns + spec->min_setup_start_ns + t->sda_fall_ns +
		spec->min_high_ns), 2));

	min_low_ns = t->scl_fall_ns + spec->min_low_ns;
	max_low_ns =  spec->max_data_hold_ns * 2 - data_hold_buffer_ns;
	min_total_ns = min_low_ns + min_high_ns;

	/* Adjust to avoid overflow */
	clk_rate_khz = DIV_ROUND_UP(clk_rate, 1000);
	scl_rate_khz = t->bus_freq_hz / 1000;

	/*
	 * We need the total div to be >= this number
	 * so we don't clock too fast.
	 */
	min_total_div = DIV_ROUND_UP(clk_rate_khz, scl_rate_khz * 8);

	/* These are the min dividers needed for min hold times. */
	min_low_div = DIV_ROUND_UP(clk_rate_khz * min_low_ns, 8 * 1000000);
	min_high_div = DIV_ROUND_UP(clk_rate_khz * min_high_ns, 8 * 1000000);
	min_div_for_hold = (min_low_div + min_high_div);

	/*
	 * This is the maximum divider so we don't go over the maximum.
	 * We don't round up here (we round down) since this is a maximum.
	 */
	max_low_div = clk_rate_khz * max_low_ns / (8 * 1000000);

	if (min_low_div > max_low_div) {
		WARN_ONCE(true,
			  "Conflicting, min_low_div %lu, max_low_div %lu\n",
			  min_low_div, max_low_div);
		max_low_div = min_low_div;
	}

	if (min_div_for_hold > min_total_div) {
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
		 */
		extra_div = min_total_div - min_div_for_hold;

		/*
		 * We'll try to split things up perfectly evenly,
		 * biasing slightly towards having a higher div
		 * for low (spend more time low).
		 */
		ideal_low_div = DIV_ROUND_UP(clk_rate_khz * min_low_ns,
					     scl_rate_khz * 8 * min_total_ns);

		/* Don't allow it to go over the maximum */
		if (ideal_low_div > max_low_div)
			ideal_low_div = max_low_div;

		/*
		 * Handle when the ideal low div is going to take up
		 * more than we have.
		 */
		if (ideal_low_div > min_low_div + extra_div)
			ideal_low_div = min_low_div + extra_div;

		/* Give low the "ideal" and give high whatever extra is left */
		extra_low_div = ideal_low_div - min_low_div;
		t_calc->div_low = ideal_low_div;
		t_calc->div_high = min_high_div + (extra_div - extra_low_div);
	}

	/*
	 * Adjust to the fact that the hardware has an implicit "+1".
	 * NOTE: Above calculations always produce div_low > 0 and div_high > 0.
	 */
	t_calc->div_low--;
	t_calc->div_high--;

	/* Give the tuning value 0, that would not update con register */
	t_calc->tuning = 0;
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