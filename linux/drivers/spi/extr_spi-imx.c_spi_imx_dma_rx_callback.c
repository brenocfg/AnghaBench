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
struct spi_imx_data {int /*<<< orphan*/  dma_rx_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spi_imx_dma_rx_callback(void *cookie)
{
	struct spi_imx_data *spi_imx = (struct spi_imx_data *)cookie;

	complete(&spi_imx->dma_rx_completion);
}