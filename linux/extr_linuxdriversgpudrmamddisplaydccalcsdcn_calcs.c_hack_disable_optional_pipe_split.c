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
struct dcn_bw_internal_vars {int /*<<< orphan*/  max_dppclk_vmin0p65; int /*<<< orphan*/ * max_dispclk; } ;

/* Variables and functions */

__attribute__((used)) static void hack_disable_optional_pipe_split(struct dcn_bw_internal_vars *v)
{
	/*
	 * disable optional pipe split by lower dispclk bounding box
	 * at DPM0
	 */
	v->max_dispclk[0] = v->max_dppclk_vmin0p65;
}