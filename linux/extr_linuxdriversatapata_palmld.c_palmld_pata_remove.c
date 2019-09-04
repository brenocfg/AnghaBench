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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_NR_PALMLD_IDE_PWEN ; 
 int /*<<< orphan*/  ata_platform_remove_one (struct platform_device*) ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palmld_hdd_gpios ; 

__attribute__((used)) static int palmld_pata_remove(struct platform_device *dev)
{
	ata_platform_remove_one(dev);

	/* power down the HDD */
	gpio_set_value(GPIO_NR_PALMLD_IDE_PWEN, 0);

	gpio_free_array(palmld_hdd_gpios, ARRAY_SIZE(palmld_hdd_gpios));

	return 0;
}