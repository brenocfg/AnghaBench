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
struct spi_nor {struct hifmc_priv* priv; } ;
struct hifmc_priv {int /*<<< orphan*/  clkrate; struct hifmc_host* host; } ;
struct hifmc_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; } ;
typedef  enum spi_nor_ops { ____Placeholder_spi_nor_ops } spi_nor_ops ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_spi_nor_prep(struct spi_nor *nor, enum spi_nor_ops ops)
{
	struct hifmc_priv *priv = nor->priv;
	struct hifmc_host *host = priv->host;
	int ret;

	mutex_lock(&host->lock);

	ret = clk_set_rate(host->clk, priv->clkrate);
	if (ret)
		goto out;

	ret = clk_prepare_enable(host->clk);
	if (ret)
		goto out;

	return 0;

out:
	mutex_unlock(&host->lock);
	return ret;
}