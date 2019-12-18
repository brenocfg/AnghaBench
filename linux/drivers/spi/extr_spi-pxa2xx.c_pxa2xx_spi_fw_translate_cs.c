#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_controller {int dummy; } ;
struct driver_data {int ssp_type; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  LPSS_BSW_SSP 129 
#define  LPSS_BYT_SSP 128 
 scalar_t__ has_acpi_companion (int /*<<< orphan*/ *) ; 
 struct driver_data* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int pxa2xx_spi_fw_translate_cs(struct spi_controller *controller,
				      unsigned int cs)
{
	struct driver_data *drv_data = spi_controller_get_devdata(controller);

	if (has_acpi_companion(&drv_data->pdev->dev)) {
		switch (drv_data->ssp_type) {
		/*
		 * For Atoms the ACPI DeviceSelection used by the Windows
		 * driver starts from 1 instead of 0 so translate it here
		 * to match what Linux expects.
		 */
		case LPSS_BYT_SSP:
		case LPSS_BSW_SSP:
			return cs - 1;

		default:
			break;
		}
	}

	return cs;
}