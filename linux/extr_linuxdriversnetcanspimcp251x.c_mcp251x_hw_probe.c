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
 int /*<<< orphan*/  CANCTRL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int mcp251x_hw_reset (struct spi_device*) ; 
 int mcp251x_read_reg (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp251x_hw_probe(struct spi_device *spi)
{
	u8 ctrl;
	int ret;

	ret = mcp251x_hw_reset(spi);
	if (ret)
		return ret;

	ctrl = mcp251x_read_reg(spi, CANCTRL);

	dev_dbg(&spi->dev, "CANCTRL 0x%02x\n", ctrl);

	/* Check for power up default value */
	if ((ctrl & 0x17) != 0x07)
		return -ENODEV;

	return 0;
}