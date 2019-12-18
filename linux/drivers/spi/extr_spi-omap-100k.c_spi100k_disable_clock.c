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
struct spi_master {int dummy; } ;
struct omap1_spi100k {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SPI_SETUP1 ; 
 unsigned int SPI_SETUP1_CLOCK_ENABLE ; 
 unsigned int readw (scalar_t__) ; 
 struct omap1_spi100k* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static void spi100k_disable_clock(struct spi_master *master)
{
	unsigned int val;
	struct omap1_spi100k *spi100k = spi_master_get_devdata(master);

	/* disable SPI */
	val = readw(spi100k->base + SPI_SETUP1);
	val &= ~SPI_SETUP1_CLOCK_ENABLE;
	writew(val, spi100k->base + SPI_SETUP1);
}