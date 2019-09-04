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
struct ti_tscadc_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IDLECONFIG ; 
 unsigned int STEPCONFIG_INM_ADCREFM ; 
 unsigned int STEPCONFIG_INP_ADCREFM ; 
 unsigned int STEPCONFIG_YNN ; 
 unsigned int STEPCONFIG_YPN ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void tscadc_idle_config(struct ti_tscadc_dev *tscadc)
{
	unsigned int idleconfig;

	idleconfig = STEPCONFIG_YNN | STEPCONFIG_INM_ADCREFM |
			STEPCONFIG_INP_ADCREFM | STEPCONFIG_YPN;

	regmap_write(tscadc->regmap, REG_IDLECONFIG, idleconfig);
}