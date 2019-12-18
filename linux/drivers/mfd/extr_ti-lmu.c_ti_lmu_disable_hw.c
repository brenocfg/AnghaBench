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
struct ti_lmu {scalar_t__ en_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_lmu_disable_hw(void *data)
{
	struct ti_lmu *lmu = data;
	if (lmu->en_gpio)
		gpiod_set_value(lmu->en_gpio, 0);
}