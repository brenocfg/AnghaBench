#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  eee; } ;
struct stmmac_priv {int tx_lpi_timer; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; TYPE_2__* hw; int /*<<< orphan*/  eee_ctrl_timer; scalar_t__ eee_enabled; scalar_t__ eee_active; TYPE_1__ dma_cap; } ;
struct TYPE_4__ {scalar_t__ pcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMMAC_DEFAULT_LIT_LS ; 
 int /*<<< orphan*/  STMMAC_LPI_T (int /*<<< orphan*/ ) ; 
 scalar_t__ STMMAC_PCS_RGMII ; 
 scalar_t__ STMMAC_PCS_RTBI ; 
 scalar_t__ STMMAC_PCS_TBI ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eee_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stmmac_eee_ctrl_timer ; 
 int /*<<< orphan*/  stmmac_set_eee_timer (struct stmmac_priv*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool stmmac_eee_init(struct stmmac_priv *priv)
{
	int tx_lpi_timer = priv->tx_lpi_timer;

	/* Using PCS we cannot dial with the phy registers at this stage
	 * so we do not support extra feature like EEE.
	 */
	if ((priv->hw->pcs == STMMAC_PCS_RGMII) ||
	    (priv->hw->pcs == STMMAC_PCS_TBI) ||
	    (priv->hw->pcs == STMMAC_PCS_RTBI))
		return false;

	/* Check if MAC core supports the EEE feature. */
	if (!priv->dma_cap.eee)
		return false;

	mutex_lock(&priv->lock);

	/* Check if it needs to be deactivated */
	if (!priv->eee_active) {
		if (priv->eee_enabled) {
			netdev_dbg(priv->dev, "disable EEE\n");
			del_timer_sync(&priv->eee_ctrl_timer);
			stmmac_set_eee_timer(priv, priv->hw, 0, tx_lpi_timer);
		}
		mutex_unlock(&priv->lock);
		return false;
	}

	if (priv->eee_active && !priv->eee_enabled) {
		timer_setup(&priv->eee_ctrl_timer, stmmac_eee_ctrl_timer, 0);
		mod_timer(&priv->eee_ctrl_timer, STMMAC_LPI_T(eee_timer));
		stmmac_set_eee_timer(priv, priv->hw, STMMAC_DEFAULT_LIT_LS,
				     tx_lpi_timer);
	}

	mutex_unlock(&priv->lock);
	netdev_dbg(priv->dev, "Energy-Efficient Ethernet initialized\n");
	return true;
}