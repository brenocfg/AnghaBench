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
typedef  int /*<<< orphan*/  uint16_t ;
struct dpp {int dummy; } ;
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 
 int /*<<< orphan*/  dpp1_cm_program_color_matrix (struct dcn10_dpp*,int /*<<< orphan*/  const*) ; 

void dpp1_cm_set_output_csc_adjustment(
		struct dpp *dpp_base,
		const uint16_t *regval)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	dpp1_cm_program_color_matrix(dpp, regval);
}