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
struct da9055 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_REG_ADC_CONT ; 
 int da9055_reg_update (struct da9055*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9055_disable_auto_mode(struct da9055 *da9055, int channel)
{

	return da9055_reg_update(da9055, DA9055_REG_ADC_CONT, 1 << channel, 0);
}