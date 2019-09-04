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
typedef  int u8 ;
typedef  enum ams_irq { ____Placeholder_ams_irq } ams_irq ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_CONTROL ; 
 int /*<<< orphan*/  AMS_FF_ENABLE ; 
 int AMS_IRQ_FREEFALL ; 
 int AMS_IRQ_GLOBAL ; 
 int AMS_IRQ_SHOCK ; 
 int /*<<< orphan*/  AMS_SHOCK_ENABLE ; 
 int ams_pmu_get_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_pmu_set_register (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ams_pmu_set_irq(enum ams_irq reg, char enable)
{
	if (reg & AMS_IRQ_FREEFALL) {
		u8 val = ams_pmu_get_register(AMS_FF_ENABLE);
		if (enable)
			val |= 0x80;
		else
			val &= ~0x80;
		ams_pmu_set_register(AMS_FF_ENABLE, val);
	}

	if (reg & AMS_IRQ_SHOCK) {
		u8 val = ams_pmu_get_register(AMS_SHOCK_ENABLE);
		if (enable)
			val |= 0x80;
		else
			val &= ~0x80;
		ams_pmu_set_register(AMS_SHOCK_ENABLE, val);
	}

	if (reg & AMS_IRQ_GLOBAL) {
		u8 val = ams_pmu_get_register(AMS_CONTROL);
		if (enable)
			val |= 0x80;
		else
			val &= ~0x80;
		ams_pmu_set_register(AMS_CONTROL, val);
	}
}