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
struct timing_generator {int dummy; } ;
struct dcp_gsl_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_ERROR (char*) ; 

__attribute__((used)) static void dce110_timing_generator_v_setup_global_swap_lock(
	struct timing_generator *tg,
	const struct dcp_gsl_params *gsl_params)
{
	DC_LOG_ERROR("Timing Sync not supported on underlay pipe\n");
	return;
}