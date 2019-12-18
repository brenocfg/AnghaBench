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
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ili9320_probe_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgg2432a4_client ; 

__attribute__((used)) static int vgg2432a4_probe(struct spi_device *spi)
{
	int ret;

	ret = ili9320_probe_spi(spi, &vgg2432a4_client);
	if (ret != 0) {
		dev_err(&spi->dev, "failed to initialise ili9320\n");
		return ret;
	}

	return 0;
}