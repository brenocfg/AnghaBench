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
typedef  unsigned char u8 ;
struct nl8048_panel {TYPE_1__* spi; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char,int) ; 
 int spi_write (TYPE_1__*,unsigned char*,int) ; 

__attribute__((used)) static int nl8048_write(struct nl8048_panel *lcd, unsigned char addr,
			unsigned char value)
{
	u8 data[4] = { value, 0x01, addr, 0x00 };
	int ret;

	ret = spi_write(lcd->spi, data, sizeof(data));
	if (ret)
		dev_err(&lcd->spi->dev, "SPI write to %u failed: %d\n",
			addr, ret);

	return ret;
}