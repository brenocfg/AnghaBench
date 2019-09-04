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
struct dpu_hw_cdm {int /*<<< orphan*/  hw; } ;
struct dpu_csc_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDM_CSC_10_MATRIX_COEFF_0 ; 
 int /*<<< orphan*/  dpu_hw_csc_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dpu_csc_cfg*,int) ; 

__attribute__((used)) static int dpu_hw_cdm_setup_csc_10bit(struct dpu_hw_cdm *ctx,
		struct dpu_csc_cfg *data)
{
	dpu_hw_csc_setup(&ctx->hw, CDM_CSC_10_MATRIX_COEFF_0, data, true);

	return 0;
}