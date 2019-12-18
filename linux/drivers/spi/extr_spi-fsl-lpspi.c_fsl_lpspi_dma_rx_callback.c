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
struct fsl_lpspi_data {int /*<<< orphan*/  dma_rx_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_lpspi_dma_rx_callback(void *cookie)
{
	struct fsl_lpspi_data *fsl_lpspi = (struct fsl_lpspi_data *)cookie;

	complete(&fsl_lpspi->dma_rx_completion);
}