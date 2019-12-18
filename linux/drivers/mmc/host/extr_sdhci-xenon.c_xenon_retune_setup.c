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
typedef  int /*<<< orphan*/  u32 ;
struct xenon_priv {int tuning_count; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int tuning_count; int /*<<< orphan*/  tuning_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_INT_RETUNE ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  SDHCI_TUNING_MODE_1 ; 
 int /*<<< orphan*/  XENON_RETUNING_COMPATIBLE ; 
 int /*<<< orphan*/  XENON_SLOT_RETUNING_REQ_CTRL ; 
 struct xenon_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xenon_retune_setup(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u32 reg;

	/* Disable the Re-Tuning Request functionality */
	reg = sdhci_readl(host, XENON_SLOT_RETUNING_REQ_CTRL);
	reg &= ~XENON_RETUNING_COMPATIBLE;
	sdhci_writel(host, reg, XENON_SLOT_RETUNING_REQ_CTRL);

	/* Disable the Re-tuning Interrupt */
	reg = sdhci_readl(host, SDHCI_SIGNAL_ENABLE);
	reg &= ~SDHCI_INT_RETUNE;
	sdhci_writel(host, reg, SDHCI_SIGNAL_ENABLE);
	reg = sdhci_readl(host, SDHCI_INT_ENABLE);
	reg &= ~SDHCI_INT_RETUNE;
	sdhci_writel(host, reg, SDHCI_INT_ENABLE);

	/* Force to use Tuning Mode 1 */
	host->tuning_mode = SDHCI_TUNING_MODE_1;
	/* Set re-tuning period */
	host->tuning_count = 1 << (priv->tuning_count - 1);
}