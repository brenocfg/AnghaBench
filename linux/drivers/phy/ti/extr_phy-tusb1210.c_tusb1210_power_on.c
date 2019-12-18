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
struct tusb1210 {scalar_t__ vendor_specific2; int /*<<< orphan*/  ulpi; int /*<<< orphan*/  gpio_cs; int /*<<< orphan*/  gpio_reset; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUSB1210_VENDOR_SPECIFIC2 ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct tusb1210* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  ulpi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tusb1210_power_on(struct phy *phy)
{
	struct tusb1210 *tusb = phy_get_drvdata(phy);

	gpiod_set_value_cansleep(tusb->gpio_reset, 1);
	gpiod_set_value_cansleep(tusb->gpio_cs, 1);

	/* Restore the optional eye diagram optimization value */
	if (tusb->vendor_specific2)
		ulpi_write(tusb->ulpi, TUSB1210_VENDOR_SPECIFIC2,
			   tusb->vendor_specific2);

	return 0;
}