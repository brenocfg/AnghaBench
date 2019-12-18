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
struct davinci_spi {int /*<<< orphan*/  done; scalar_t__ rcount; int /*<<< orphan*/  wcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void davinci_spi_dma_rx_callback(void *data)
{
	struct davinci_spi *dspi = (struct davinci_spi *)data;

	dspi->rcount = 0;

	if (!dspi->wcount && !dspi->rcount)
		complete(&dspi->done);
}