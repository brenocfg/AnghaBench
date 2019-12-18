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
struct fsl_lpspi_data {int /*<<< orphan*/  (* rx ) (struct fsl_lpspi_data*) ;scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IMX7ULP_RSR ; 
 int RSR_RXEMPTY ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct fsl_lpspi_data*) ; 

__attribute__((used)) static void fsl_lpspi_read_rx_fifo(struct fsl_lpspi_data *fsl_lpspi)
{
	while (!(readl(fsl_lpspi->base + IMX7ULP_RSR) & RSR_RXEMPTY))
		fsl_lpspi->rx(fsl_lpspi);
}