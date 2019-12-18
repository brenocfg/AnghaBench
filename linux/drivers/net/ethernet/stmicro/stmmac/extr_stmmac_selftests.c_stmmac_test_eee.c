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
struct TYPE_2__ {int /*<<< orphan*/  eee; } ;
struct stmmac_priv {int /*<<< orphan*/  xstats; int /*<<< orphan*/  eee_active; TYPE_1__ dma_cap; } ;
struct stmmac_extra_stats {scalar_t__ irq_tx_path_in_lpi_mode_n; scalar_t__ irq_tx_path_exit_lpi_mode_n; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct stmmac_extra_stats*) ; 
 struct stmmac_extra_stats* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct stmmac_extra_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stmmac_test_mac_loopback (struct stmmac_priv*) ; 

__attribute__((used)) static int stmmac_test_eee(struct stmmac_priv *priv)
{
	struct stmmac_extra_stats *initial, *final;
	int retries = 10;
	int ret;

	if (!priv->dma_cap.eee || !priv->eee_active)
		return -EOPNOTSUPP;

	initial = kzalloc(sizeof(*initial), GFP_KERNEL);
	if (!initial)
		return -ENOMEM;

	final = kzalloc(sizeof(*final), GFP_KERNEL);
	if (!final) {
		ret = -ENOMEM;
		goto out_free_initial;
	}

	memcpy(initial, &priv->xstats, sizeof(*initial));

	ret = stmmac_test_mac_loopback(priv);
	if (ret)
		goto out_free_final;

	/* We have no traffic in the line so, sooner or later it will go LPI */
	while (--retries) {
		memcpy(final, &priv->xstats, sizeof(*final));

		if (final->irq_tx_path_in_lpi_mode_n >
		    initial->irq_tx_path_in_lpi_mode_n)
			break;
		msleep(100);
	}

	if (!retries) {
		ret = -ETIMEDOUT;
		goto out_free_final;
	}

	if (final->irq_tx_path_in_lpi_mode_n <=
	    initial->irq_tx_path_in_lpi_mode_n) {
		ret = -EINVAL;
		goto out_free_final;
	}

	if (final->irq_tx_path_exit_lpi_mode_n <=
	    initial->irq_tx_path_exit_lpi_mode_n) {
		ret = -EINVAL;
		goto out_free_final;
	}

out_free_final:
	kfree(final);
out_free_initial:
	kfree(initial);
	return ret;
}