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
 int dataflash_status (struct spi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dataflash_waitready(struct spi_device *spi)
{
	int	status;

	for (;;) {
		status = dataflash_status(spi);
		if (status < 0) {
			dev_dbg(&spi->dev, "status %d?\n", status);
			status = 0;
		}

		if (status & (1 << 7))	/* RDY/nBSY */
			return status;

		usleep_range(3000, 4000);
	}
}