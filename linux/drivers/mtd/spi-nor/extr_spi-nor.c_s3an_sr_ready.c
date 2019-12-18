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
struct spi_nor {int* bouncebuf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XSR_RDY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int spi_nor_xread_sr (struct spi_nor*,int*) ; 

__attribute__((used)) static int s3an_sr_ready(struct spi_nor *nor)
{
	int ret;

	ret = spi_nor_xread_sr(nor, nor->bouncebuf);
	if (ret < 0) {
		dev_err(nor->dev, "error %d reading XRDSR\n", (int) ret);
		return ret;
	}

	return !!(nor->bouncebuf[0] & XSR_RDY);
}