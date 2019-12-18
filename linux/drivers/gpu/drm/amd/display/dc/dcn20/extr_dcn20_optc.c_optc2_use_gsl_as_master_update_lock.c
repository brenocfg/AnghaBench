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
struct optc {int dummy; } ;
struct gsl_params {int /*<<< orphan*/  master_update_lock_gsl_en; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_GSL_CONTROL ; 
 int /*<<< orphan*/  OTG_MASTER_UPDATE_LOCK_GSL_EN ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void optc2_use_gsl_as_master_update_lock(struct timing_generator *optc,
		   const struct gsl_params *params)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE(OTG_GSL_CONTROL,
		OTG_MASTER_UPDATE_LOCK_GSL_EN, params->master_update_lock_gsl_en);
}