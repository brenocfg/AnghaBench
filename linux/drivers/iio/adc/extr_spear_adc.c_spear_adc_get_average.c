#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct spear_adc_state {TYPE_3__* adc_base_spear3xx; TYPE_2__* adc_base_spear6xx; int /*<<< orphan*/  np; } ;
struct TYPE_6__ {int /*<<< orphan*/  average; } ;
struct TYPE_4__ {int /*<<< orphan*/  msb; } ;
struct TYPE_5__ {TYPE_1__ average; } ;

/* Variables and functions */
 int SPEAR_ADC_DATA_MASK ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u32 spear_adc_get_average(struct spear_adc_state *st)
{
	if (of_device_is_compatible(st->np, "st,spear600-adc")) {
		return __raw_readl(&st->adc_base_spear6xx->average.msb) &
			SPEAR_ADC_DATA_MASK;
	} else {
		return __raw_readl(&st->adc_base_spear3xx->average) &
			SPEAR_ADC_DATA_MASK;
	}
}