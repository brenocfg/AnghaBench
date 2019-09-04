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
struct cxd2880_spi_device {int dummy; } ;
struct cxd2880_spi {struct cxd2880_spi_device* user; scalar_t__ flags; int /*<<< orphan*/  write_read; int /*<<< orphan*/  write; int /*<<< orphan*/ * read; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cxd2880_spi_device_write ; 
 int /*<<< orphan*/  cxd2880_spi_device_write_read ; 

int cxd2880_spi_device_create_spi(struct cxd2880_spi *spi,
				  struct cxd2880_spi_device *spi_device)
{
	if (!spi || !spi_device)
		return -EINVAL;

	spi->read = NULL;
	spi->write = cxd2880_spi_device_write;
	spi->write_read = cxd2880_spi_device_write_read;
	spi->flags = 0;
	spi->user = spi_device;

	return 0;
}