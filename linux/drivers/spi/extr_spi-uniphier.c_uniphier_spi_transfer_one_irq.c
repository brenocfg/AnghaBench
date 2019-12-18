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
struct uniphier_spi_priv {int error; int /*<<< orphan*/  xfer_done; } ;
struct spi_transfer {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct spi_master {TYPE_1__ dev; } ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int SSI_IE_RCIE ; 
 int SSI_IE_RORIE ; 
 int /*<<< orphan*/  SSI_TIMEOUT_MS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct uniphier_spi_priv* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  uniphier_spi_fill_tx_fifo (struct uniphier_spi_priv*) ; 
 int /*<<< orphan*/  uniphier_spi_irq_disable (struct spi_device*,int) ; 
 int /*<<< orphan*/  uniphier_spi_irq_enable (struct spi_device*,int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_spi_transfer_one_irq(struct spi_master *master,
					 struct spi_device *spi,
					 struct spi_transfer *t)
{
	struct uniphier_spi_priv *priv = spi_master_get_devdata(master);
	struct device *dev = master->dev.parent;
	unsigned long time_left;

	reinit_completion(&priv->xfer_done);

	uniphier_spi_fill_tx_fifo(priv);

	uniphier_spi_irq_enable(spi, SSI_IE_RCIE | SSI_IE_RORIE);

	time_left = wait_for_completion_timeout(&priv->xfer_done,
					msecs_to_jiffies(SSI_TIMEOUT_MS));

	uniphier_spi_irq_disable(spi, SSI_IE_RCIE | SSI_IE_RORIE);

	if (!time_left) {
		dev_err(dev, "transfer timeout.\n");
		return -ETIMEDOUT;
	}

	return priv->error;
}