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
struct spi_device_id {int /*<<< orphan*/  name; int /*<<< orphan*/  driver_data; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ad5686_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad5686_spi_read ; 
 int /*<<< orphan*/  ad5686_spi_write ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int ad5686_spi_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);

	return ad5686_probe(&spi->dev, id->driver_data, id->name,
			    ad5686_spi_write, ad5686_spi_read);
}