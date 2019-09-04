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
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_GAMUT_REMAP_CONTROL ; 
 int /*<<< orphan*/  CM_GAMUT_REMAP_MODE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dpp_set_gamut_remap_bypass(struct dcn10_dpp *dpp)
{
	REG_SET(CM_GAMUT_REMAP_CONTROL, 0,
			CM_GAMUT_REMAP_MODE, 0);
	/* Gamut remap in bypass */
}