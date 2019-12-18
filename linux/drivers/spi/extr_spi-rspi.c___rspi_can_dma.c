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
struct spi_transfer {scalar_t__ len; } ;
struct rspi_data {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ fifo_size; } ;

/* Variables and functions */

__attribute__((used)) static bool __rspi_can_dma(const struct rspi_data *rspi,
			   const struct spi_transfer *xfer)
{
	return xfer->len > rspi->ops->fifo_size;
}