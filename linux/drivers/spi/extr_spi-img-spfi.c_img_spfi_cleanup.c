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
struct spi_device {int /*<<< orphan*/  cs_gpio; } ;
struct img_spfi_device_data {scalar_t__ gpio_requested; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct img_spfi_device_data*) ; 
 struct img_spfi_device_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_spfi_cleanup(struct spi_device *spi)
{
	struct img_spfi_device_data *spfi_data = spi_get_ctldata(spi);

	if (spfi_data) {
		if (spfi_data->gpio_requested)
			gpio_free(spi->cs_gpio);
		kfree(spfi_data);
		spi_set_ctldata(spi, NULL);
	}
}