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
struct fsl_dspi_dma {int /*<<< orphan*/  cmd_tx_complete; } ;
struct fsl_dspi {struct fsl_dspi_dma* dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dspi_tx_dma_callback(void *arg)
{
	struct fsl_dspi *dspi = arg;
	struct fsl_dspi_dma *dma = dspi->dma;

	complete(&dma->cmd_tx_complete);
}