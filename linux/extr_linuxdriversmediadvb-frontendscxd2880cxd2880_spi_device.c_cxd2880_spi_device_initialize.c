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
typedef  int /*<<< orphan*/  u32 ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  mode; } ;
struct cxd2880_spi_device {struct spi_device* spi; } ;
typedef  enum cxd2880_spi_mode { ____Placeholder_cxd2880_spi_mode } cxd2880_spi_mode ;

/* Variables and functions */
#define  CXD2880_SPI_MODE_0 131 
#define  CXD2880_SPI_MODE_1 130 
#define  CXD2880_SPI_MODE_2 129 
#define  CXD2880_SPI_MODE_3 128 
 int EINVAL ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  SPI_MODE_1 ; 
 int /*<<< orphan*/  SPI_MODE_2 ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int spi_setup (struct spi_device*) ; 

int
cxd2880_spi_device_initialize(struct cxd2880_spi_device *spi_device,
			      enum cxd2880_spi_mode mode,
			      u32 speed_hz)
{
	int result = 0;
	struct spi_device *spi = spi_device->spi;

	switch (mode) {
	case CXD2880_SPI_MODE_0:
		spi->mode = SPI_MODE_0;
		break;
	case CXD2880_SPI_MODE_1:
		spi->mode = SPI_MODE_1;
		break;
	case CXD2880_SPI_MODE_2:
		spi->mode = SPI_MODE_2;
		break;
	case CXD2880_SPI_MODE_3:
		spi->mode = SPI_MODE_3;
		break;
	default:
		return -EINVAL;
	}

	spi->max_speed_hz = speed_hz;
	spi->bits_per_word = 8;
	result = spi_setup(spi);
	if (result != 0) {
		pr_err("spi_setup failed %d\n", result);
		return -EINVAL;
	}

	return 0;
}