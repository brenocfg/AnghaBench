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
struct ktd2692_context {int /*<<< orphan*/  ctrl_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTD2692_HIGH ; 
 int /*<<< orphan*/  KTD2692_LOW ; 
 int /*<<< orphan*/  KTD2692_TIME_HIGH_END_OF_DATA_US ; 
 int /*<<< orphan*/  KTD2692_TIME_LOW_END_OF_DATA_US ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ktd2692_expresswire_end(struct ktd2692_context *led)
{
	gpiod_direction_output(led->ctrl_gpio, KTD2692_LOW);
	udelay(KTD2692_TIME_LOW_END_OF_DATA_US);
	gpiod_direction_output(led->ctrl_gpio, KTD2692_HIGH);
	udelay(KTD2692_TIME_HIGH_END_OF_DATA_US);
}