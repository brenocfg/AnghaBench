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
struct xtfpga_spi {int dummy; } ;

/* Variables and functions */
 unsigned int BUSY_WAIT_US ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  XTFPGA_SPI_BUSY ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ xtfpga_spi_read32 (struct xtfpga_spi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xtfpga_spi_wait_busy(struct xtfpga_spi *xspi)
{
	unsigned i;

	for (i = 0; xtfpga_spi_read32(xspi, XTFPGA_SPI_BUSY) &&
	     i < BUSY_WAIT_US; ++i)
		udelay(1);
	WARN_ON_ONCE(i == BUSY_WAIT_US);
}