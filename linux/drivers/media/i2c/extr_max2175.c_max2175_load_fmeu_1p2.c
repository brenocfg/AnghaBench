#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max2175 {int decim_ratio; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  MAX2175_CH_MSEL ; 
 int /*<<< orphan*/  MAX2175_EQ_MSEL ; 
 int /*<<< orphan*/  ch_coeff_fmeu ; 
 int /*<<< orphan*/  eq_coeff_fmeu1_ra02_m6db ; 
 TYPE_1__* fmeu1p2_map ; 
 int /*<<< orphan*/  max2175_set_filter_coeffs (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_write (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max2175_load_fmeu_1p2(struct max2175 *ctx)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(fmeu1p2_map); i++)
		max2175_write(ctx, fmeu1p2_map[i].idx, fmeu1p2_map[i].val);

	ctx->decim_ratio = 36;

	/* Load the Channel Filter Coefficients into channel filter bank #2 */
	max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 0, ch_coeff_fmeu);
	max2175_set_filter_coeffs(ctx, MAX2175_EQ_MSEL, 0,
				  eq_coeff_fmeu1_ra02_m6db);
}