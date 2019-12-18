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
struct dpp_cursor_attributes {int /*<<< orphan*/  scale; int /*<<< orphan*/  bias; } ;
struct dpp {int dummy; } ;
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUR0_FP_BIAS ; 
 int /*<<< orphan*/  CUR0_FP_SCALE ; 
 int /*<<< orphan*/  CURSOR0_FP_SCALE_BIAS ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp1_cnv_set_optional_cursor_attributes(
		struct dpp *dpp_base,
		struct dpp_cursor_attributes *attr)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	if (attr) {
		REG_UPDATE(CURSOR0_FP_SCALE_BIAS,  CUR0_FP_BIAS,  attr->bias);
		REG_UPDATE(CURSOR0_FP_SCALE_BIAS,  CUR0_FP_SCALE, attr->scale);
	}
}