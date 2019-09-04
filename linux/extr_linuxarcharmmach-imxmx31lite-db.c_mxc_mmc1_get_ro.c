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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMUX_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MX31_PIN_GPIO1_6 ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxc_mmc1_get_ro(struct device *dev)
{
	return gpio_get_value(IOMUX_TO_GPIO(MX31_PIN_GPIO1_6));
}