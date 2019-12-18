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
struct spi_lm70llp {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assertCS (struct spi_lm70llp*) ; 
 int /*<<< orphan*/  deassertCS (struct spi_lm70llp*) ; 
 struct spi_lm70llp* spidev_to_pp (struct spi_device*) ; 

__attribute__((used)) static void lm70_chipselect(struct spi_device *spi, int value)
{
	struct spi_lm70llp *pp = spidev_to_pp(spi);

	if (value)
		assertCS(pp);
	else
		deassertCS(pp);
}