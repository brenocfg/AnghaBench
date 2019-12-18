#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mwl8k_priv {int sniffer_enabled; int wmm_enabled; int fw_rev; TYPE_2__* pdev; scalar_t__ regs; scalar_t__ ap_fw; int /*<<< orphan*/  hw_rev; TYPE_1__* device_info; int /*<<< orphan*/  ampdu; int /*<<< orphan*/  hw_restart_in_progress; scalar_t__ num_ampdu_queues; int /*<<< orphan*/  watchdog_event_pending; scalar_t__ pending_tx_pkts; int /*<<< orphan*/ * rxd_ops; } ;
struct ieee80211_hw {TYPE_3__* wiphy; struct mwl8k_priv* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  perm_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {int /*<<< orphan*/  part_name; int /*<<< orphan*/ * ap_rxd_ops; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int MWL8K_A2H_EVENTS ; 
 int MWL8K_A2H_INT_BA_WATCHDOG ; 
 int MWL8K_A2H_INT_OPC_DONE ; 
 int MWL8K_A2H_INT_RX_READY ; 
 int MWL8K_A2H_INT_TX_DONE ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_CLEAR_SEL ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_MASK ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_STATUS ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK ; 
 int /*<<< orphan*/  MWL8K_NAME ; 
 int /*<<< orphan*/  MWL8K_RF_ANTENNA_RX ; 
 int /*<<< orphan*/  MWL8K_RF_ANTENNA_TX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mwl8k_cmd_get_hw_spec_ap (struct ieee80211_hw*) ; 
 int mwl8k_cmd_get_hw_spec_sta (struct ieee80211_hw*) ; 
 int mwl8k_cmd_radio_disable (struct ieee80211_hw*) ; 
 int mwl8k_cmd_rf_antenna (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 int mwl8k_cmd_set_hw_spec (struct ieee80211_hw*) ; 
 int mwl8k_cmd_set_mac_addr (struct ieee80211_hw*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mwl8k_hw_reset (struct mwl8k_priv*) ; 
 int mwl8k_init_txqs (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_interrupt ; 
 int /*<<< orphan*/  mwl8k_rxq_deinit (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int mwl8k_rxq_init (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int mwl8k_tx_queues (struct mwl8k_priv*) ; 
 int /*<<< orphan*/  mwl8k_txq_deinit (struct ieee80211_hw*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rxd_sta_ops ; 
 int /*<<< orphan*/  rxq_refill (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  wiphy_info (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  wiphy_warn (TYPE_3__*,char*) ; 

__attribute__((used)) static int mwl8k_probe_hw(struct ieee80211_hw *hw)
{
	struct mwl8k_priv *priv = hw->priv;
	int rc = 0;
	int i;

	if (priv->ap_fw) {
		priv->rxd_ops = priv->device_info->ap_rxd_ops;
		if (priv->rxd_ops == NULL) {
			wiphy_err(hw->wiphy,
				  "Driver does not have AP firmware image support for this hardware\n");
			rc = -ENOENT;
			goto err_stop_firmware;
		}
	} else {
		priv->rxd_ops = &rxd_sta_ops;
	}

	priv->sniffer_enabled = false;
	priv->wmm_enabled = false;
	priv->pending_tx_pkts = 0;
	atomic_set(&priv->watchdog_event_pending, 0);

	rc = mwl8k_rxq_init(hw, 0);
	if (rc)
		goto err_stop_firmware;
	rxq_refill(hw, 0, INT_MAX);

	/* For the sta firmware, we need to know the dma addresses of tx queues
	 * before sending MWL8K_CMD_GET_HW_SPEC.  So we must initialize them
	 * prior to issuing this command.  But for the AP case, we learn the
	 * total number of queues from the result CMD_GET_HW_SPEC, so for this
	 * case we must initialize the tx queues after.
	 */
	priv->num_ampdu_queues = 0;
	if (!priv->ap_fw) {
		rc = mwl8k_init_txqs(hw);
		if (rc)
			goto err_free_queues;
	}

	iowrite32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	iowrite32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	iowrite32(MWL8K_A2H_INT_TX_DONE|MWL8K_A2H_INT_RX_READY|
		  MWL8K_A2H_INT_BA_WATCHDOG,
		  priv->regs + MWL8K_HIU_A2H_INTERRUPT_CLEAR_SEL);
	iowrite32(MWL8K_A2H_INT_OPC_DONE,
		  priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK);

	rc = request_irq(priv->pdev->irq, mwl8k_interrupt,
			 IRQF_SHARED, MWL8K_NAME, hw);
	if (rc) {
		wiphy_err(hw->wiphy, "failed to register IRQ handler\n");
		goto err_free_queues;
	}

	/*
	 * When hw restart is requested,
	 * mac80211 will take care of clearing
	 * the ampdu streams, so do not clear
	 * the ampdu state here
	 */
	if (!priv->hw_restart_in_progress)
		memset(priv->ampdu, 0, sizeof(priv->ampdu));

	/*
	 * Temporarily enable interrupts.  Initial firmware host
	 * commands use interrupts and avoid polling.  Disable
	 * interrupts when done.
	 */
	iowrite32(MWL8K_A2H_EVENTS, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);

	/* Get config data, mac addrs etc */
	if (priv->ap_fw) {
		rc = mwl8k_cmd_get_hw_spec_ap(hw);
		if (!rc)
			rc = mwl8k_init_txqs(hw);
		if (!rc)
			rc = mwl8k_cmd_set_hw_spec(hw);
	} else {
		rc = mwl8k_cmd_get_hw_spec_sta(hw);
	}
	if (rc) {
		wiphy_err(hw->wiphy, "Cannot initialise firmware\n");
		goto err_free_irq;
	}

	/* Turn radio off */
	rc = mwl8k_cmd_radio_disable(hw);
	if (rc) {
		wiphy_err(hw->wiphy, "Cannot disable\n");
		goto err_free_irq;
	}

	/* Clear MAC address */
	rc = mwl8k_cmd_set_mac_addr(hw, NULL, "\x00\x00\x00\x00\x00\x00");
	if (rc) {
		wiphy_err(hw->wiphy, "Cannot clear MAC address\n");
		goto err_free_irq;
	}

	/* Configure Antennas */
	rc = mwl8k_cmd_rf_antenna(hw, MWL8K_RF_ANTENNA_RX, 0x3);
	if (rc)
		wiphy_warn(hw->wiphy, "failed to set # of RX antennas");
	rc = mwl8k_cmd_rf_antenna(hw, MWL8K_RF_ANTENNA_TX, 0x7);
	if (rc)
		wiphy_warn(hw->wiphy, "failed to set # of TX antennas");


	/* Disable interrupts */
	iowrite32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	free_irq(priv->pdev->irq, hw);

	wiphy_info(hw->wiphy, "%s v%d, %pm, %s firmware %u.%u.%u.%u\n",
		   priv->device_info->part_name,
		   priv->hw_rev, hw->wiphy->perm_addr,
		   priv->ap_fw ? "AP" : "STA",
		   (priv->fw_rev >> 24) & 0xff, (priv->fw_rev >> 16) & 0xff,
		   (priv->fw_rev >> 8) & 0xff, priv->fw_rev & 0xff);

	return 0;

err_free_irq:
	iowrite32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	free_irq(priv->pdev->irq, hw);

err_free_queues:
	for (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_deinit(hw, i);
	mwl8k_rxq_deinit(hw, 0);

err_stop_firmware:
	mwl8k_hw_reset(priv);

	return rc;
}