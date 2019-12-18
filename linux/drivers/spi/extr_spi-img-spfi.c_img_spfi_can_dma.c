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
struct spi_transfer {scalar_t__ len; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SPFI_32BIT_FIFO_SIZE ; 

__attribute__((used)) static bool img_spfi_can_dma(struct spi_master *master, struct spi_device *spi,
			     struct spi_transfer *xfer)
{
	if (xfer->len > SPFI_32BIT_FIFO_SIZE)
		return true;
	return false;
}