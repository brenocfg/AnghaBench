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
 int /*<<< orphan*/  IOMUX_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MX31_PIN_NFCE_B ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qong_nand_select_chip(struct mtd_info *mtd, int chip)
{
	if (chip >= 0)
		gpio_set_value(IOMUX_TO_GPIO(MX31_PIN_NFCE_B), 0);
	else
		gpio_set_value(IOMUX_TO_GPIO(MX31_PIN_NFCE_B), 1);
}