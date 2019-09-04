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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOSA_GPIO_CARD_VCC_ON ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tosa_tc6393xb_teardown(struct platform_device *dev)
{
	gpio_free(TOSA_GPIO_CARD_VCC_ON);
}