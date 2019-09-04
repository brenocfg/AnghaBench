#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ad7793_state {TYPE_1__* chip_info; } ;
struct ad7793_platform_data {scalar_t__ current_source_direction; scalar_t__ exitation_current; scalar_t__ clock_src; scalar_t__ refsel; scalar_t__ bias_voltage; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ AD7793_BIAS_VOLTAGE_DISABLED ; 
 scalar_t__ AD7793_CLK_SRC_INT ; 
 int AD7793_FLAG_HAS_CLKSEL ; 
 int AD7793_FLAG_HAS_REFSEL ; 
 int AD7793_FLAG_HAS_VBIAS ; 
 int AD7793_HAS_EXITATION_CURRENT ; 
 scalar_t__ AD7793_IEXEC1_IEXEC2_IOUT1 ; 
 scalar_t__ AD7793_IEXEC1_IEXEC2_IOUT2 ; 
 scalar_t__ AD7793_IX_10uA ; 
 scalar_t__ AD7793_IX_210uA ; 
 scalar_t__ AD7793_IX_DISABLED ; 
 scalar_t__ AD7793_REFSEL_REFIN1 ; 
 int EINVAL ; 

__attribute__((used)) static int ad7793_check_platform_data(struct ad7793_state *st,
	const struct ad7793_platform_data *pdata)
{
	if ((pdata->current_source_direction == AD7793_IEXEC1_IEXEC2_IOUT1 ||
		pdata->current_source_direction == AD7793_IEXEC1_IEXEC2_IOUT2) &&
		((pdata->exitation_current != AD7793_IX_10uA) &&
		(pdata->exitation_current != AD7793_IX_210uA)))
		return -EINVAL;

	if (!(st->chip_info->flags & AD7793_FLAG_HAS_CLKSEL) &&
		pdata->clock_src != AD7793_CLK_SRC_INT)
		return -EINVAL;

	if (!(st->chip_info->flags & AD7793_FLAG_HAS_REFSEL) &&
		pdata->refsel != AD7793_REFSEL_REFIN1)
		return -EINVAL;

	if (!(st->chip_info->flags & AD7793_FLAG_HAS_VBIAS) &&
		pdata->bias_voltage != AD7793_BIAS_VOLTAGE_DISABLED)
		return -EINVAL;

	if (!(st->chip_info->flags & AD7793_HAS_EXITATION_CURRENT) &&
		pdata->exitation_current != AD7793_IX_DISABLED)
		return -EINVAL;

	return 0;
}