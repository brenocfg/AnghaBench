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

/* Variables and functions */
 int /*<<< orphan*/  PCH_SRST ; 
 int /*<<< orphan*/  pch_spi_writereg (struct spi_master*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pch_spi_reset(struct spi_master *master)
{
	/* write 1 to reset SPI */
	pch_spi_writereg(master, PCH_SRST, 0x1);

	/* clear reset */
	pch_spi_writereg(master, PCH_SRST, 0x0);
}