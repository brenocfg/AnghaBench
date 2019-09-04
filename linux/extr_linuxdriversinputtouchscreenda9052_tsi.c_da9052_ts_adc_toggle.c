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
struct da9052_tsi {int adc_on; int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_TSI_CONT_A_REG ; 
 int /*<<< orphan*/  da9052_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void da9052_ts_adc_toggle(struct da9052_tsi *tsi, bool on)
{
	da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG, 1 << 0, on);
	tsi->adc_on = on;
}