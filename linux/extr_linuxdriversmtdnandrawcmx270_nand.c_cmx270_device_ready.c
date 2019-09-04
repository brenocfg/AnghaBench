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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_NAND_RB ; 
 int /*<<< orphan*/  dsb () ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmx270_device_ready(struct mtd_info *mtd)
{
	dsb();

	return (gpio_get_value(GPIO_NAND_RB));
}