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
typedef  int /*<<< orphan*/  u8 ;
struct ad7314_data {int /*<<< orphan*/  rx; TYPE_1__* spi_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int spi_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad7314_spi_read(struct ad7314_data *chip)
{
	int ret;

	ret = spi_read(chip->spi_dev, (u8 *)&chip->rx, sizeof(chip->rx));
	if (ret < 0) {
		dev_err(&chip->spi_dev->dev, "SPI read error\n");
		return ret;
	}

	return be16_to_cpu(chip->rx);
}