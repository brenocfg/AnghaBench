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
struct gsl_params {int /*<<< orphan*/  gsl_master_mode; int /*<<< orphan*/  gsl_master_en; int /*<<< orphan*/  gsl2_en; int /*<<< orphan*/  gsl1_en; int /*<<< orphan*/  gsl0_en; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_GSL0_EN ; 
 int /*<<< orphan*/  OTG_GSL1_EN ; 
 int /*<<< orphan*/  OTG_GSL2_EN ; 
 int /*<<< orphan*/  OTG_GSL_CONTROL ; 
 int /*<<< orphan*/  OTG_GSL_MASTER_EN ; 
 int /*<<< orphan*/  OTG_GSL_MASTER_MODE ; 
 int /*<<< orphan*/  REG_UPDATE_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void optc2_set_gsl(struct timing_generator *optc,
		   const struct gsl_params *params)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

/**
 * There are (MAX_OPTC+1)/2 gsl groups available for use.
 * In each group (assign an OTG to a group by setting OTG_GSLX_EN = 1,
 * set one of the OTGs to be the master (OTG_GSL_MASTER_EN = 1) and the rest are slaves.
 */
	REG_UPDATE_5(OTG_GSL_CONTROL,
		OTG_GSL0_EN, params->gsl0_en,
		OTG_GSL1_EN, params->gsl1_en,
		OTG_GSL2_EN, params->gsl2_en,
		OTG_GSL_MASTER_EN, params->gsl_master_en,
		OTG_GSL_MASTER_MODE, params->gsl_master_mode);
}