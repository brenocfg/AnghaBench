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
struct tegra_i2c_dev {int /*<<< orphan*/ * rx_dma_chan; int /*<<< orphan*/ * tx_dma_chan; int /*<<< orphan*/ * dma_buf; int /*<<< orphan*/  dma_phys; int /*<<< orphan*/  dma_buf_size; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_i2c_release_dma(struct tegra_i2c_dev *i2c_dev)
{
	if (i2c_dev->dma_buf) {
		dma_free_coherent(i2c_dev->dev, i2c_dev->dma_buf_size,
				  i2c_dev->dma_buf, i2c_dev->dma_phys);
		i2c_dev->dma_buf = NULL;
	}

	if (i2c_dev->tx_dma_chan) {
		dma_release_channel(i2c_dev->tx_dma_chan);
		i2c_dev->tx_dma_chan = NULL;
	}

	if (i2c_dev->rx_dma_chan) {
		dma_release_channel(i2c_dev->rx_dma_chan);
		i2c_dev->rx_dma_chan = NULL;
	}
}