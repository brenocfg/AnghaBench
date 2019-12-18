#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_10__ {int /*<<< orphan*/ * txq; } ;
struct ath_softc {int /*<<< orphan*/  tx99_skb; TYPE_5__ tx; struct ath_hw* sc_ah; int /*<<< orphan*/  hw_check_work; int /*<<< orphan*/  hw_pll_work; int /*<<< orphan*/  paprd_work; int /*<<< orphan*/  hw_reset_work; int /*<<< orphan*/  sleep_timer; int /*<<< orphan*/  bcon_tasklet; int /*<<< orphan*/  intr_tq; int /*<<< orphan*/  mutex; int /*<<< orphan*/  chan_lock; int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  sc_serial_rw; int /*<<< orphan*/  intr_lock; int /*<<< orphan*/  hw; TYPE_2__* cur_chan; TYPE_2__* chanctx; int /*<<< orphan*/  tx_wait; scalar_t__ tx99_power; int /*<<< orphan*/  dfs_detector; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int led_active_high; } ;
struct TYPE_8__ {int /*<<< orphan*/  rmw; int /*<<< orphan*/  write; int /*<<< orphan*/  multi_read; int /*<<< orphan*/  read; } ;
struct ath9k_hw_capabilities {int hw_caps; } ;
struct TYPE_6__ {int /*<<< orphan*/  devid; } ;
struct ath_hw {int led_pin; TYPE_4__ config; TYPE_3__ reg_ops; struct ath9k_hw_capabilities caps; int /*<<< orphan*/  ah_flags; TYPE_1__ hw_version; int /*<<< orphan*/  hw; int /*<<< orphan*/  dev; } ;
struct ath_common {int btcoex_enabled; int disable_ani; int bt_ant_diversity; int cachelsz; struct ath_bus_ops const* bus_ops; int /*<<< orphan*/  cc_lock; int /*<<< orphan*/  debug_mask; struct ath_softc* priv; int /*<<< orphan*/  hw; struct ath_hw* ah; int /*<<< orphan*/ * ps_ops; TYPE_3__* ops; int /*<<< orphan*/  op_flags; } ;
struct ath_bus_ops {int /*<<< orphan*/  (* aspm_init ) (struct ath_common*) ;} ;
struct TYPE_7__ {scalar_t__ hw_queue_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_USE_EEPROM ; 
 int ATH9K_HW_CAP_BT_ANT_DIV ; 
 int ATH9K_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  ATH_OP_INVALID ; 
 scalar_t__ ATH_TXQ_SETUP (struct ath_softc*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_RATE_POWER ; 
 int /*<<< orphan*/  NL80211_DFS_UNSET ; 
 int /*<<< orphan*/  ath9k_beacon_tasklet ; 
 scalar_t__ ath9k_bt_ant_diversity ; 
 int ath9k_btcoex_enable ; 
 int ath9k_cmn_init_channels_rates (struct ath_common*) ; 
 int /*<<< orphan*/  ath9k_cmn_init_crypto (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_debug ; 
 int /*<<< orphan*/  ath9k_eeprom_release (struct ath_softc*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_deinit (struct ath_hw*) ; 
 int ath9k_hw_init (struct ath_hw*) ; 
 int ath9k_init_btcoex (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_init_channel_context (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_init_misc (struct ath_softc*) ; 
 int ath9k_init_p2p (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_init_pcoem_platform (struct ath_softc*) ; 
 int ath9k_init_platform (struct ath_softc*) ; 
 int ath9k_init_queues (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ioread32 ; 
 int /*<<< orphan*/  ath9k_iowrite32 ; 
 int /*<<< orphan*/  ath9k_is_chanctx_enabled () ; 
 int ath9k_led_active_high ; 
 int /*<<< orphan*/  ath9k_multi_ioread32 ; 
 int ath9k_of_init (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_offchannel_init (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_ops ; 
 int /*<<< orphan*/  ath9k_reg_rmw ; 
 int /*<<< orphan*/  ath9k_tasklet ; 
 int /*<<< orphan*/  ath_chanctx_init (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hw_check_work ; 
 int /*<<< orphan*/  ath_hw_pll_work ; 
 int /*<<< orphan*/  ath_paprd_calibrate ; 
 int /*<<< orphan*/  ath_ps_full_sleep ; 
 int /*<<< orphan*/  ath_read_cachesize (struct ath_common*,int*) ; 
 int /*<<< orphan*/  ath_reset_work ; 
 int /*<<< orphan*/  ath_tx_cleanupq (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 struct ath_hw* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfs_pattern_detector_init (struct ath_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ath_common*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_init_softc(u16 devid, struct ath_softc *sc,
			    const struct ath_bus_ops *bus_ops)
{
	struct ath_hw *ah = NULL;
	struct ath9k_hw_capabilities *pCap;
	struct ath_common *common;
	int ret = 0, i;
	int csz = 0;

	ah = devm_kzalloc(sc->dev, sizeof(struct ath_hw), GFP_KERNEL);
	if (!ah)
		return -ENOMEM;

	ah->dev = sc->dev;
	ah->hw = sc->hw;
	ah->hw_version.devid = devid;
	ah->ah_flags |= AH_USE_EEPROM;
	ah->led_pin = -1;
	ah->reg_ops.read = ath9k_ioread32;
	ah->reg_ops.multi_read = ath9k_multi_ioread32;
	ah->reg_ops.write = ath9k_iowrite32;
	ah->reg_ops.rmw = ath9k_reg_rmw;
	pCap = &ah->caps;

	common = ath9k_hw_common(ah);

	/* Will be cleared in ath9k_start() */
	set_bit(ATH_OP_INVALID, &common->op_flags);

	sc->sc_ah = ah;
	sc->dfs_detector = dfs_pattern_detector_init(common, NL80211_DFS_UNSET);
	sc->tx99_power = MAX_RATE_POWER + 1;
	init_waitqueue_head(&sc->tx_wait);
	sc->cur_chan = &sc->chanctx[0];
	if (!ath9k_is_chanctx_enabled())
		sc->cur_chan->hw_queue_base = 0;

	common->ops = &ah->reg_ops;
	common->bus_ops = bus_ops;
	common->ps_ops = &ath9k_ps_ops;
	common->ah = ah;
	common->hw = sc->hw;
	common->priv = sc;
	common->debug_mask = ath9k_debug;
	common->btcoex_enabled = ath9k_btcoex_enable == 1;
	common->disable_ani = false;

	/*
	 * Platform quirks.
	 */
	ath9k_init_pcoem_platform(sc);

	ret = ath9k_init_platform(sc);
	if (ret)
		return ret;

	ret = ath9k_of_init(sc);
	if (ret)
		return ret;

	if (ath9k_led_active_high != -1)
		ah->config.led_active_high = ath9k_led_active_high == 1;

	/*
	 * Enable WLAN/BT RX Antenna diversity only when:
	 *
	 * - BTCOEX is disabled.
	 * - the user manually requests the feature.
	 * - the HW cap is set using the platform data.
	 */
	if (!common->btcoex_enabled && ath9k_bt_ant_diversity &&
	    (pCap->hw_caps & ATH9K_HW_CAP_BT_ANT_DIV))
		common->bt_ant_diversity = 1;

	spin_lock_init(&common->cc_lock);
	spin_lock_init(&sc->intr_lock);
	spin_lock_init(&sc->sc_serial_rw);
	spin_lock_init(&sc->sc_pm_lock);
	spin_lock_init(&sc->chan_lock);
	mutex_init(&sc->mutex);
	tasklet_init(&sc->intr_tq, ath9k_tasklet, (unsigned long)sc);
	tasklet_init(&sc->bcon_tasklet, ath9k_beacon_tasklet,
		     (unsigned long)sc);

	timer_setup(&sc->sleep_timer, ath_ps_full_sleep, 0);
	INIT_WORK(&sc->hw_reset_work, ath_reset_work);
	INIT_WORK(&sc->paprd_work, ath_paprd_calibrate);
	INIT_DELAYED_WORK(&sc->hw_pll_work, ath_hw_pll_work);
	INIT_DELAYED_WORK(&sc->hw_check_work, ath_hw_check_work);

	ath9k_init_channel_context(sc);

	/*
	 * Cache line size is used to size and align various
	 * structures used to communicate with the hardware.
	 */
	ath_read_cachesize(common, &csz);
	common->cachelsz = csz << 2; /* convert to bytes */

	/* Initializes the hardware for all supported chipsets */
	ret = ath9k_hw_init(ah);
	if (ret)
		goto err_hw;

	ret = ath9k_init_queues(sc);
	if (ret)
		goto err_queues;

	ret =  ath9k_init_btcoex(sc);
	if (ret)
		goto err_btcoex;

	ret = ath9k_cmn_init_channels_rates(common);
	if (ret)
		goto err_btcoex;

	ret = ath9k_init_p2p(sc);
	if (ret)
		goto err_btcoex;

	ath9k_cmn_init_crypto(sc->sc_ah);
	ath9k_init_misc(sc);
	ath_chanctx_init(sc);
	ath9k_offchannel_init(sc);

	if (common->bus_ops->aspm_init)
		common->bus_ops->aspm_init(common);

	return 0;

err_btcoex:
	for (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		if (ATH_TXQ_SETUP(sc, i))
			ath_tx_cleanupq(sc, &sc->tx.txq[i]);
err_queues:
	ath9k_hw_deinit(ah);
err_hw:
	ath9k_eeprom_release(sc);
	dev_kfree_skb_any(sc->tx99_skb);
	return ret;
}