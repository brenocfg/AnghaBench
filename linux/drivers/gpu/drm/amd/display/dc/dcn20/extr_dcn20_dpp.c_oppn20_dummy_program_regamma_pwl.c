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
struct pwl_params {int dummy; } ;
struct dpp {int dummy; } ;
typedef  enum opp_regamma { ____Placeholder_opp_regamma } opp_regamma ;

/* Variables and functions */

void oppn20_dummy_program_regamma_pwl(
		struct dpp *dpp,
		const struct pwl_params *params,
		enum opp_regamma mode)
{}