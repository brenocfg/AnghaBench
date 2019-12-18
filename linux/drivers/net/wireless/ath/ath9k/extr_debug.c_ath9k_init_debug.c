#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  rxstats; } ;
struct TYPE_14__ {int /*<<< orphan*/  debugfs_phy; TYPE_3__ stats; } ;
struct ath_softc {TYPE_6__ debug; TYPE_7__* sc_ah; int /*<<< orphan*/  dev; int /*<<< orphan*/  spec_priv; TYPE_2__* hw; } ;
struct TYPE_13__ {int /*<<< orphan*/  cwm_ignore_extcca; } ;
struct ath_hw {TYPE_5__ config; int /*<<< orphan*/  txchainmask; int /*<<< orphan*/  rxchainmask; } ;
struct ath_common {scalar_t__ priv; } ;
struct TYPE_12__ {int /*<<< orphan*/  enable_paprd; } ;
struct TYPE_15__ {int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_mask; TYPE_4__ config; } ;
struct TYPE_10__ {TYPE_1__* wiphy; } ;
struct TYPE_9__ {int /*<<< orphan*/  debugfsdir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ath9k_cmn_debug_base_eeprom (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ath9k_cmn_debug_modal_eeprom (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ath9k_cmn_debug_phy_err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_cmn_debug_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_cmn_spectral_init_debug (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_dfs_init_debug (struct ath_softc*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_tx99_init_debug (struct ath_softc*) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_devm_seqfile (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_ackto ; 
 int /*<<< orphan*/  fops_ani ; 
 int /*<<< orphan*/  fops_antenna_diversity ; 
 int /*<<< orphan*/  fops_bt_ant_diversity ; 
 int /*<<< orphan*/  fops_btcoex ; 
 int /*<<< orphan*/  fops_debug ; 
 int /*<<< orphan*/  fops_nf_override ; 
 int /*<<< orphan*/  fops_regdump ; 
 int /*<<< orphan*/  fops_regidx ; 
 int /*<<< orphan*/  fops_regval ; 
 int /*<<< orphan*/  fops_tpc ; 
 int /*<<< orphan*/  fops_wow ; 
 int /*<<< orphan*/  read_file_dma ; 
 int /*<<< orphan*/  read_file_dump_nfcal ; 
 int /*<<< orphan*/  read_file_interrupt ; 
 int /*<<< orphan*/  read_file_misc ; 
 int /*<<< orphan*/  read_file_queues ; 
 int /*<<< orphan*/  read_file_reset ; 
 int /*<<< orphan*/  read_file_xmit ; 

int ath9k_init_debug(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_softc *sc = (struct ath_softc *) common->priv;

	sc->debug.debugfs_phy = debugfs_create_dir("ath9k",
						   sc->hw->wiphy->debugfsdir);
	if (!sc->debug.debugfs_phy)
		return -ENOMEM;

#ifdef CONFIG_ATH_DEBUG
	debugfs_create_file("debug", 0600, sc->debug.debugfs_phy,
			    sc, &fops_debug);
#endif

	ath9k_dfs_init_debug(sc);
	ath9k_tx99_init_debug(sc);
	ath9k_cmn_spectral_init_debug(&sc->spec_priv, sc->debug.debugfs_phy);

	debugfs_create_devm_seqfile(sc->dev, "dma", sc->debug.debugfs_phy,
				    read_file_dma);
	debugfs_create_devm_seqfile(sc->dev, "interrupt", sc->debug.debugfs_phy,
				    read_file_interrupt);
	debugfs_create_devm_seqfile(sc->dev, "xmit", sc->debug.debugfs_phy,
				    read_file_xmit);
	debugfs_create_devm_seqfile(sc->dev, "queues", sc->debug.debugfs_phy,
				    read_file_queues);
	debugfs_create_devm_seqfile(sc->dev, "misc", sc->debug.debugfs_phy,
				    read_file_misc);
	debugfs_create_devm_seqfile(sc->dev, "reset", sc->debug.debugfs_phy,
				    read_file_reset);

	ath9k_cmn_debug_recv(sc->debug.debugfs_phy, &sc->debug.stats.rxstats);
	ath9k_cmn_debug_phy_err(sc->debug.debugfs_phy, &sc->debug.stats.rxstats);

	debugfs_create_u8("rx_chainmask", 0400, sc->debug.debugfs_phy,
			  &ah->rxchainmask);
	debugfs_create_u8("tx_chainmask", 0400, sc->debug.debugfs_phy,
			  &ah->txchainmask);
	debugfs_create_file("ani", 0600,
			    sc->debug.debugfs_phy, sc, &fops_ani);
	debugfs_create_bool("paprd", 0600, sc->debug.debugfs_phy,
			    &sc->sc_ah->config.enable_paprd);
	debugfs_create_file("regidx", 0600, sc->debug.debugfs_phy,
			    sc, &fops_regidx);
	debugfs_create_file("regval", 0600, sc->debug.debugfs_phy,
			    sc, &fops_regval);
	debugfs_create_bool("ignore_extcca", 0600,
			    sc->debug.debugfs_phy,
			    &ah->config.cwm_ignore_extcca);
	debugfs_create_file("regdump", 0400, sc->debug.debugfs_phy, sc,
			    &fops_regdump);
	debugfs_create_devm_seqfile(sc->dev, "dump_nfcal",
				    sc->debug.debugfs_phy,
				    read_file_dump_nfcal);

	ath9k_cmn_debug_base_eeprom(sc->debug.debugfs_phy, sc->sc_ah);
	ath9k_cmn_debug_modal_eeprom(sc->debug.debugfs_phy, sc->sc_ah);

	debugfs_create_u32("gpio_mask", 0600,
			   sc->debug.debugfs_phy, &sc->sc_ah->gpio_mask);
	debugfs_create_u32("gpio_val", 0600,
			   sc->debug.debugfs_phy, &sc->sc_ah->gpio_val);
	debugfs_create_file("antenna_diversity", 0400,
			    sc->debug.debugfs_phy, sc, &fops_antenna_diversity);
#ifdef CONFIG_ATH9K_BTCOEX_SUPPORT
	debugfs_create_file("bt_ant_diversity", 0600,
			    sc->debug.debugfs_phy, sc, &fops_bt_ant_diversity);
	debugfs_create_file("btcoex", 0400, sc->debug.debugfs_phy, sc,
			    &fops_btcoex);
#endif

#ifdef CONFIG_ATH9K_WOW
	debugfs_create_file("wow", 0600, sc->debug.debugfs_phy, sc, &fops_wow);
#endif

#ifdef CONFIG_ATH9K_DYNACK
	debugfs_create_file("ack_to", 0400, sc->debug.debugfs_phy,
			    sc, &fops_ackto);
#endif
	debugfs_create_file("tpc", 0600, sc->debug.debugfs_phy, sc, &fops_tpc);

	debugfs_create_file("nf_override", 0600,
			    sc->debug.debugfs_phy, sc, &fops_nf_override);

	return 0;
}