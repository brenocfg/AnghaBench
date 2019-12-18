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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct cxd2880_spi_device {int /*<<< orphan*/  spi; } ;
struct cxd2880_spi {struct cxd2880_spi_device* user; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int spi_write_then_read (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxd2880_spi_device_write_read(struct cxd2880_spi *spi,
					 const u8 *tx_data,
					 u32 tx_size,
					 u8 *rx_data,
					 u32 rx_size)
{
	struct cxd2880_spi_device *spi_device = NULL;
	int result = 0;

	if (!spi || !spi->user || !tx_data ||
	    !tx_size || !rx_data || !rx_size)
		return -EINVAL;

	spi_device = spi->user;

	result = spi_write_then_read(spi_device->spi, tx_data,
				     tx_size, rx_data, rx_size);
	if (result < 0)
		return -EIO;

	return 0;
}