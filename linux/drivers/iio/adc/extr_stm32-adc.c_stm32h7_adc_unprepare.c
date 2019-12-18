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
struct stm32_adc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stm32h7_adc_disable (struct stm32_adc*) ; 
 int /*<<< orphan*/  stm32h7_adc_enter_pwr_down (struct stm32_adc*) ; 

__attribute__((used)) static void stm32h7_adc_unprepare(struct stm32_adc *adc)
{
	stm32h7_adc_disable(adc);
	stm32h7_adc_enter_pwr_down(adc);
}