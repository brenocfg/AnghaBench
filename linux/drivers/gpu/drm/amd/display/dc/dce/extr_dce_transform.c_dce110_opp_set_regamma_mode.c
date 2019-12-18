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
struct transform {int dummy; } ;
struct dce_transform {int dummy; } ;
typedef  enum opp_regamma { ____Placeholder_opp_regamma } opp_regamma ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_REGAMMA_MODE ; 
 int /*<<< orphan*/  REGAMMA_CONTROL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dce_transform* TO_DCE_TRANSFORM (struct transform*) ; 

void dce110_opp_set_regamma_mode(struct transform *xfm,
				 enum opp_regamma mode)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);

	REG_SET(REGAMMA_CONTROL, 0,
		GRPH_REGAMMA_MODE, mode);
}