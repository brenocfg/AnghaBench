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
struct platform_device {int dummy; } ;
struct lantiq_ssc_spi {int /*<<< orphan*/  fpi_clk; int /*<<< orphan*/  spi_clk; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_CLC ; 
 int /*<<< orphan*/  LTQ_SPI_IRNEN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_enter_config_mode (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  lantiq_ssc_writel (struct lantiq_ssc_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lantiq_ssc_spi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rx_fifo_flush (struct lantiq_ssc_spi*) ; 
 int /*<<< orphan*/  tx_fifo_flush (struct lantiq_ssc_spi*) ; 

__attribute__((used)) static int lantiq_ssc_remove(struct platform_device *pdev)
{
	struct lantiq_ssc_spi *spi = platform_get_drvdata(pdev);

	lantiq_ssc_writel(spi, 0, LTQ_SPI_IRNEN);
	lantiq_ssc_writel(spi, 0, LTQ_SPI_CLC);
	rx_fifo_flush(spi);
	tx_fifo_flush(spi);
	hw_enter_config_mode(spi);

	destroy_workqueue(spi->wq);
	clk_disable_unprepare(spi->spi_clk);
	clk_put(spi->fpi_clk);

	return 0;
}