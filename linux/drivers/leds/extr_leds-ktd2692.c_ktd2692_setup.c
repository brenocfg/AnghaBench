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
struct ktd2692_context {int /*<<< orphan*/  aux_gpio; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int KTD2692_FLASH_MODE_CURR_PERCENT (int) ; 
 int /*<<< orphan*/  KTD2692_LOW ; 
 int KTD2692_MM_MIN_CURR_THRESHOLD_SCALE ; 
 int /*<<< orphan*/  KTD2692_MODE_DISABLE ; 
 int KTD2692_REG_FLASH_CURRENT_BASE ; 
 int KTD2692_REG_MM_MIN_CURR_THRESHOLD_BASE ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktd2692_expresswire_reset (struct ktd2692_context*) ; 
 int /*<<< orphan*/  ktd2692_expresswire_write (struct ktd2692_context*,int) ; 

__attribute__((used)) static void ktd2692_setup(struct ktd2692_context *led)
{
	led->mode = KTD2692_MODE_DISABLE;
	ktd2692_expresswire_reset(led);
	gpiod_direction_output(led->aux_gpio, KTD2692_LOW);

	ktd2692_expresswire_write(led, (KTD2692_MM_MIN_CURR_THRESHOLD_SCALE - 1)
				 | KTD2692_REG_MM_MIN_CURR_THRESHOLD_BASE);
	ktd2692_expresswire_write(led, KTD2692_FLASH_MODE_CURR_PERCENT(45)
				 | KTD2692_REG_FLASH_CURRENT_BASE);
}