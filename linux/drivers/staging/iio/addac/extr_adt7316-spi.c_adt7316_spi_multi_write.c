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

/* Variables and functions */
 int ADT7316_REG_MAX_ADDR ; 
 int ADT7316_SPI_CMD_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int spi_write (struct spi_device*,int*,int) ; 

__attribute__((used)) static int adt7316_spi_multi_write(void *client, u8 reg, u8 count, u8 *data)
{
	struct spi_device *spi_dev = client;
	u8 buf[ADT7316_REG_MAX_ADDR + 2];
	int i, ret;

	if (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	buf[0] = ADT7316_SPI_CMD_WRITE;
	buf[1] = reg;
	for (i = 0; i < count; i++)
		buf[i + 2] = data[i];

	ret = spi_write(spi_dev, buf, count + 2);
	if (ret < 0) {
		dev_err(&spi_dev->dev, "SPI write error\n");
		return ret;
	}

	return ret;
}