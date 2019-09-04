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
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RN5T618_REPCNT ; 
 int /*<<< orphan*/  RN5T618_REPCNT_REPWRON ; 
 int /*<<< orphan*/  RN5T618_SLPCNT ; 
 int /*<<< orphan*/  RN5T618_SLPCNT_SWPWROFF ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* rn5t618_pm_power_off ; 

__attribute__((used)) static void rn5t618_trigger_poweroff_sequence(bool repower)
{
	/* disable automatic repower-on */
	regmap_update_bits(rn5t618_pm_power_off->regmap, RN5T618_REPCNT,
			   RN5T618_REPCNT_REPWRON,
			   repower ? RN5T618_REPCNT_REPWRON : 0);
	/* start power-off sequence */
	regmap_update_bits(rn5t618_pm_power_off->regmap, RN5T618_SLPCNT,
			   RN5T618_SLPCNT_SWPWROFF, RN5T618_SLPCNT_SWPWROFF);
}