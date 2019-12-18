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
typedef  int u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct max31722_data {int mode; struct spi_device* spi_device; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAX31722_MODE_MASK ; 
 int MAX31722_REG_CFG ; 
 int MAX31722_WRITE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int spi_write (struct spi_device*,int**,int) ; 

__attribute__((used)) static int max31722_set_mode(struct max31722_data *data, u8 mode)
{
	int ret;
	struct spi_device *spi = data->spi_device;
	u8 buf[2] = {
		MAX31722_REG_CFG | MAX31722_WRITE_MASK,
		(data->mode & MAX31722_MODE_MASK) | mode
	};

	ret = spi_write(spi, &buf, sizeof(buf));
	if (ret < 0) {
		dev_err(&spi->dev, "failed to set sensor mode.\n");
		return ret;
	}
	data->mode = (data->mode & MAX31722_MODE_MASK) | mode;

	return 0;
}