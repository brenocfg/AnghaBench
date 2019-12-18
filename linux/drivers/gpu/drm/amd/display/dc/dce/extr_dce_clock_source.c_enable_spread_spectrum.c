#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ EXTERNAL_SS; scalar_t__ CENTER_SPREAD; } ;
struct spread_spectrum_data {TYPE_3__ flags; int /*<<< orphan*/  percentage; } ;
struct pll_settings {int calculated_pix_clk_100hz; scalar_t__ ss_percentage; } ;
struct delta_sigma_data {int /*<<< orphan*/  ds_frac_amount; int /*<<< orphan*/  ds_frac_size; int /*<<< orphan*/  nfrac_amount; int /*<<< orphan*/  feedback_amount; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct dce110_clk_src {TYPE_6__* bios; TYPE_2__ base; } ;
struct TYPE_10__ {int DS_TYPE; int CENTER_SPREAD; int EXTERNAL_SS; } ;
struct TYPE_7__ {int /*<<< orphan*/  ds_frac_size; int /*<<< orphan*/  nfrac_amount; int /*<<< orphan*/  feedback_amount; } ;
struct bp_spread_spectrum_parameters {TYPE_4__ flags; int /*<<< orphan*/  percentage; int /*<<< orphan*/  pll_id; int /*<<< orphan*/  ds_frac_amount; TYPE_1__ ds; int /*<<< orphan*/  member_0; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
struct TYPE_12__ {TYPE_5__* funcs; } ;
struct TYPE_11__ {scalar_t__ (* enable_spread_spectrum_on_ppll ) (TYPE_6__*,struct bp_spread_spectrum_parameters*,int) ;} ;

/* Variables and functions */
 scalar_t__ BP_RESULT_OK ; 
 scalar_t__ calculate_ss (struct pll_settings*,struct spread_spectrum_data const*,struct delta_sigma_data*) ; 
 struct spread_spectrum_data* get_ss_data_entry (struct dce110_clk_src*,int,int) ; 
 scalar_t__ stub1 (TYPE_6__*,struct bp_spread_spectrum_parameters*,int) ; 

__attribute__((used)) static bool enable_spread_spectrum(
		struct dce110_clk_src *clk_src,
		enum signal_type signal, struct pll_settings *pll_settings)
{
	struct bp_spread_spectrum_parameters bp_params = {0};
	struct delta_sigma_data d_s_data;
	const struct spread_spectrum_data *ss_data = NULL;

	ss_data = get_ss_data_entry(
			clk_src,
			signal,
			pll_settings->calculated_pix_clk_100hz / 10);

/* Pixel clock PLL has been programmed to generate desired pixel clock,
 * now enable SS on pixel clock */
/* TODO is it OK to return true not doing anything ??*/
	if (ss_data != NULL && pll_settings->ss_percentage != 0) {
		if (calculate_ss(pll_settings, ss_data, &d_s_data)) {
			bp_params.ds.feedback_amount =
					d_s_data.feedback_amount;
			bp_params.ds.nfrac_amount =
					d_s_data.nfrac_amount;
			bp_params.ds.ds_frac_size = d_s_data.ds_frac_size;
			bp_params.ds_frac_amount =
					d_s_data.ds_frac_amount;
			bp_params.flags.DS_TYPE = 1;
			bp_params.pll_id = clk_src->base.id;
			bp_params.percentage = ss_data->percentage;
			if (ss_data->flags.CENTER_SPREAD)
				bp_params.flags.CENTER_SPREAD = 1;
			if (ss_data->flags.EXTERNAL_SS)
				bp_params.flags.EXTERNAL_SS = 1;

			if (BP_RESULT_OK !=
				clk_src->bios->funcs->
					enable_spread_spectrum_on_ppll(
							clk_src->bios,
							&bp_params,
							true))
				return false;
		} else
			return false;
	}
	return true;
}