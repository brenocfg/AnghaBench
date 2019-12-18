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
typedef  int u32 ;
struct sprd_spi {scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct spi_transfer {int dummy; } ;

/* Variables and functions */
 scalar_t__ SPRD_SPI_INT_CLR ; 
 scalar_t__ SPRD_SPI_INT_RAW_STS ; 
 int /*<<< orphan*/  SPRD_SPI_RX_END_INT_CLR ; 
 int SPRD_SPI_RX_END_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int sprd_spi_transfer_max_timeout (struct sprd_spi*,struct spi_transfer*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sprd_spi_wait_for_rx_end(struct sprd_spi *ss, struct spi_transfer *t)
{
	u32 val, us;
	int ret;

	us = sprd_spi_transfer_max_timeout(ss, t);
	ret = readl_relaxed_poll_timeout(ss->base + SPRD_SPI_INT_RAW_STS, val,
					 val & SPRD_SPI_RX_END_IRQ, 0, us);
	if (ret) {
		dev_err(ss->dev, "SPI error, spi rx timeout!\n");
		return ret;
	}

	writel_relaxed(SPRD_SPI_RX_END_INT_CLR, ss->base + SPRD_SPI_INT_CLR);

	return 0;
}