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
struct da9052 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_ADCCONT_AUTOVDDEN ; 
 int /*<<< orphan*/  DA9052_ADC_CONT_REG ; 
 int da9052_reg_update (struct da9052*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int da9052_disable_vddout_channel(struct da9052 *da9052)
{
	return da9052_reg_update(da9052, DA9052_ADC_CONT_REG,
				 DA9052_ADCCONT_AUTOVDDEN, 0);
}