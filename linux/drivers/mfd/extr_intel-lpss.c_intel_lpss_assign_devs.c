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
struct mfd_cell {int dummy; } ;
struct intel_lpss {unsigned int caps; unsigned int type; int /*<<< orphan*/  cell; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  LPSS_DEV_I2C 130 
#define  LPSS_DEV_SPI 129 
#define  LPSS_DEV_UART 128 
 unsigned int LPSS_PRIV_CAPS_TYPE_MASK ; 
 unsigned int LPSS_PRIV_CAPS_TYPE_SHIFT ; 
 int /*<<< orphan*/  devm_kmemdup (int /*<<< orphan*/ ,struct mfd_cell const*,int,int /*<<< orphan*/ ) ; 
 struct mfd_cell intel_lpss_i2c_cell ; 
 struct mfd_cell intel_lpss_spi_cell ; 
 struct mfd_cell intel_lpss_uart_cell ; 

__attribute__((used)) static int intel_lpss_assign_devs(struct intel_lpss *lpss)
{
	const struct mfd_cell *cell;
	unsigned int type;

	type = lpss->caps & LPSS_PRIV_CAPS_TYPE_MASK;
	type >>= LPSS_PRIV_CAPS_TYPE_SHIFT;

	switch (type) {
	case LPSS_DEV_I2C:
		cell = &intel_lpss_i2c_cell;
		break;
	case LPSS_DEV_UART:
		cell = &intel_lpss_uart_cell;
		break;
	case LPSS_DEV_SPI:
		cell = &intel_lpss_spi_cell;
		break;
	default:
		return -ENODEV;
	}

	lpss->cell = devm_kmemdup(lpss->dev, cell, sizeof(*cell), GFP_KERNEL);
	if (!lpss->cell)
		return -ENOMEM;

	lpss->type = type;

	return 0;
}