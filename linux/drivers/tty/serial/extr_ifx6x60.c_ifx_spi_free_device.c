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
struct ifx_spi_device {int /*<<< orphan*/  rx_bus; int /*<<< orphan*/  rx_buffer; TYPE_1__* spi_dev; int /*<<< orphan*/  tx_bus; int /*<<< orphan*/  tx_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_SPI_TRANSFER_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifx_spi_free_port (struct ifx_spi_device*) ; 

__attribute__((used)) static void ifx_spi_free_device(struct ifx_spi_device *ifx_dev)
{
	ifx_spi_free_port(ifx_dev);
	dma_free_coherent(&ifx_dev->spi_dev->dev,
				IFX_SPI_TRANSFER_SIZE,
				ifx_dev->tx_buffer,
				ifx_dev->tx_bus);
	dma_free_coherent(&ifx_dev->spi_dev->dev,
				IFX_SPI_TRANSFER_SIZE,
				ifx_dev->rx_buffer,
				ifx_dev->rx_bus);
}