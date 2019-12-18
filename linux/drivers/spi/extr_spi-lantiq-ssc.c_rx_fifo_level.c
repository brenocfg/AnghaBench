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
typedef  unsigned int u32 ;
struct lantiq_ssc_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_FSTAT ; 
 unsigned int LTQ_SPI_FSTAT_RXFFL_M ; 
 unsigned int lantiq_ssc_readl (struct lantiq_ssc_spi const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int rx_fifo_level(const struct lantiq_ssc_spi *spi)
{
	u32 fstat = lantiq_ssc_readl(spi, LTQ_SPI_FSTAT);

	return fstat & LTQ_SPI_FSTAT_RXFFL_M;
}