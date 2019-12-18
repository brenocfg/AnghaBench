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
typedef  int u32 ;
struct max2175 {int decim_ratio; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX2175_CH_MSEL ; 
 int /*<<< orphan*/  MAX2175_EQ_MSEL ; 
#define  MAX2175_NA_FM_1_0 129 
#define  MAX2175_NA_FM_2_0 128 
 int /*<<< orphan*/  ch_coeff_fmna ; 
 int /*<<< orphan*/  eq_coeff_fmna1_ra02_m6db ; 
 int /*<<< orphan*/  max2175_load_fmna_1p0 (struct max2175*) ; 
 int /*<<< orphan*/  max2175_load_fmna_2p0 (struct max2175*) ; 
 int /*<<< orphan*/  max2175_set_filter_coeffs (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_write_bit (struct max2175*,int,int,int) ; 

__attribute__((used)) static void max2175_set_na_rx_mode(struct max2175 *ctx, u32 rx_mode)
{
	switch (rx_mode) {
	case MAX2175_NA_FM_1_0:
		max2175_load_fmna_1p0(ctx);
		break;
	case MAX2175_NA_FM_2_0:
		max2175_load_fmna_2p0(ctx);
		break;
	}
	/* Master is the default setting */
	if (!ctx->master)
		max2175_write_bit(ctx, 30, 7, 1);

	ctx->decim_ratio = 27;

	/* Load the Channel Filter Coefficients into channel filter bank #2 */
	max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 0, ch_coeff_fmna);
	max2175_set_filter_coeffs(ctx, MAX2175_EQ_MSEL, 0,
				  eq_coeff_fmna1_ra02_m6db);
}