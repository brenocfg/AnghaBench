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
struct stm32_qspi {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ QSPI_CR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_master_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_qspi_dma_free (struct stm32_qspi*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32_qspi_release(struct stm32_qspi *qspi)
{
	/* disable qspi */
	writel_relaxed(0, qspi->io_base + QSPI_CR);
	stm32_qspi_dma_free(qspi);
	mutex_destroy(&qspi->lock);
	clk_disable_unprepare(qspi->clk);
	spi_master_put(qspi->ctrl);
}