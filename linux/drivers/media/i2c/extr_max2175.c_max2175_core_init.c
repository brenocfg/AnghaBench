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
struct max2175 {scalar_t__ xtal_freq; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX2175_CH_MSEL ; 
 int /*<<< orphan*/  MAX2175_EQ_MSEL ; 
 scalar_t__ MAX2175_EU_XTAL_FREQ ; 
 int /*<<< orphan*/  ch_coeff_fmeu ; 
 int /*<<< orphan*/  ch_coeff_fmna ; 
 int /*<<< orphan*/  eq_coeff_fmeu1_ra02_m6db ; 
 int /*<<< orphan*/  eq_coeff_fmna1_ra02_m6db ; 
 int max2175_init_power_manager (struct max2175*) ; 
 int /*<<< orphan*/  max2175_load_adc_presets (struct max2175*) ; 
 int /*<<< orphan*/  max2175_load_from_rom (struct max2175*) ; 
 int /*<<< orphan*/  max2175_load_full_fm_eu_1p0 (struct max2175*) ; 
 int /*<<< orphan*/  max2175_load_full_fm_na_1p0 (struct max2175*) ; 
 int max2175_recalibrate_adc (struct max2175*) ; 
 int /*<<< orphan*/  max2175_set_filter_coeffs (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_write_bit (struct max2175*,int,int,int) ; 
 int /*<<< orphan*/  max2175_write_bits (struct max2175*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,...) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int max2175_core_init(struct max2175 *ctx, u32 refout_bits)
{
	int ret;

	/* MAX2175 uses 36.864MHz clock for EU & 40.154MHz for NA region */
	if (ctx->xtal_freq == MAX2175_EU_XTAL_FREQ)
		max2175_load_full_fm_eu_1p0(ctx);
	else
		max2175_load_full_fm_na_1p0(ctx);

	/* The default settings assume master */
	if (!ctx->master)
		max2175_write_bit(ctx, 30, 7, 1);

	mxm_dbg(ctx, "refout_bits %u\n", refout_bits);

	/* Set REFOUT */
	max2175_write_bits(ctx, 56, 7, 5, refout_bits);

	/* ADC Reset */
	max2175_write_bit(ctx, 99, 1, 0);
	usleep_range(1000, 1500);
	max2175_write_bit(ctx, 99, 1, 1);

	/* Load ADC preset values */
	max2175_load_adc_presets(ctx);

	/* Initialize the power management state machine */
	ret = max2175_init_power_manager(ctx);
	if (ret)
		return ret;

	/* Recalibrate ADC */
	ret = max2175_recalibrate_adc(ctx);
	if (ret)
		return ret;

	/* Load ROM values to appropriate registers */
	max2175_load_from_rom(ctx);

	if (ctx->xtal_freq == MAX2175_EU_XTAL_FREQ) {
		/* Load FIR coefficients into bank 0 */
		max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 0,
					  ch_coeff_fmeu);
		max2175_set_filter_coeffs(ctx, MAX2175_EQ_MSEL, 0,
					  eq_coeff_fmeu1_ra02_m6db);
	} else {
		/* Load FIR coefficients into bank 0 */
		max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 0,
					  ch_coeff_fmna);
		max2175_set_filter_coeffs(ctx, MAX2175_EQ_MSEL, 0,
					  eq_coeff_fmna1_ra02_m6db);
	}
	mxm_dbg(ctx, "core initialized\n");

	return 0;
}