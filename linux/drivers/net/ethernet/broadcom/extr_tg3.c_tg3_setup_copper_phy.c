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
typedef  void* u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ active_speed; scalar_t__ active_duplex; scalar_t__ autoneg; int speed; void* duplex; scalar_t__ rmt_adv; } ;
struct tg3 {int mi_mode; int phy_id; int phy_flags; scalar_t__ led_ctrl; int mac_mode; int /*<<< orphan*/  pdev; TYPE_1__ link_config; scalar_t__ link_up; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5700 ; 
 scalar_t__ ASIC_REV_5701 ; 
 scalar_t__ ASIC_REV_5703 ; 
 scalar_t__ ASIC_REV_5704 ; 
 scalar_t__ ASIC_REV_5705 ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMSR_LSTATUS ; 
 scalar_t__ CHIPREV_ID_5700_ALTIMA ; 
 scalar_t__ CHIPREV_ID_5701_A0 ; 
 scalar_t__ CHIPREV_ID_5701_B0 ; 
 int /*<<< orphan*/  CLKREQ_BUG ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 void* DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  INIT_COMPLETE ; 
 int LED_CTRL_1000MBPS_ON ; 
 int LED_CTRL_100MBPS_ON ; 
 int LED_CTRL_LNKLED_OVERRIDE ; 
 scalar_t__ LED_CTRL_MODE_PHY_1 ; 
 int /*<<< orphan*/  MAC_EVENT ; 
 int MAC_EVENT_LNKSTATE_CHANGED ; 
 int /*<<< orphan*/  MAC_LED_CTRL ; 
 int /*<<< orphan*/  MAC_MI_MODE ; 
 int MAC_MI_MODE_AUTO_POLL ; 
 int /*<<< orphan*/  MAC_MODE ; 
 int MAC_MODE_HALF_DUPLEX ; 
 int MAC_MODE_LINK_POLARITY ; 
 int MAC_MODE_PORT_INT_LPBACK ; 
 int MAC_MODE_PORT_MODE_GMII ; 
 int MAC_MODE_PORT_MODE_MASK ; 
 int MAC_MODE_PORT_MODE_MII ; 
 int /*<<< orphan*/  MAC_STATUS ; 
 int MAC_STATUS_CFG_CHANGED ; 
 int MAC_STATUS_SYNC_CHANGED ; 
 int MII_BMCR ; 
 int MII_BMSR ; 
 int /*<<< orphan*/  MII_TG3_AUXCTL_SHDWSEL_MISCTEST ; 
 int /*<<< orphan*/  MII_TG3_AUXCTL_SHDWSEL_PWRCTL ; 
 int MII_TG3_AUX_STAT ; 
 int MII_TG3_EXT_CTRL ; 
 int MII_TG3_EXT_CTRL_LNK3_LED_MODE ; 
 int MII_TG3_EXT_STAT ; 
 int MII_TG3_EXT_STAT_MDIX ; 
 int MII_TG3_FET_GEN_STAT ; 
 int MII_TG3_FET_GEN_STAT_MDIXSTAT ; 
 int MII_TG3_IMASK ; 
 int MII_TG3_INT_LINKCHG ; 
 int MII_TG3_ISTAT ; 
 int MII_TG3_MISC_SHDW ; 
 int /*<<< orphan*/  NIC_SRAM_FIRMWARE_MBOX ; 
 int /*<<< orphan*/  NIC_SRAM_FIRMWARE_MBOX_MAGIC2 ; 
 int /*<<< orphan*/  PCIX_MODE ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL_CLKREQ_EN ; 
 int /*<<< orphan*/  PCI_HIGH_SPEED ; 
 int /*<<< orphan*/  RGMII_MODE ; 
 int /*<<< orphan*/  ROBOSWITCH ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int SPEED_UNKNOWN ; 
 int TG3_PHYFLG_CAPACITIVE_COUPLING ; 
 int TG3_PHYFLG_IS_FET ; 
 int TG3_PHYFLG_IS_LOW_POWER ; 
 int TG3_PHYFLG_KEEP_LINK_ON_PWRDN ; 
 int TG3_PHYFLG_MDIX_STATE ; 
 int TG3_PHYFLG_USE_MI_INTERRUPT ; 
 int TG3_PHY_ID_BCM5401 ; 
 int TG3_PHY_ID_BCM5411 ; 
 int TG3_PHY_ID_MASK ; 
 int TG3_PHY_ID_REV_MASK ; 
 int TG3_PHY_REV_BCM5401_B0 ; 
 int /*<<< orphan*/  USE_LINKCHG_REG ; 
 int /*<<< orphan*/  pcie_capability_clear_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_set_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_5700_link_polarity (struct tg3*,scalar_t__) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_aux_stat_to_speed_duplex (struct tg3*,int,int*,void**) ; 
 scalar_t__ tg3_chip_rev_id (struct tg3*) ; 
 int /*<<< orphan*/  tg3_clear_mac_status (struct tg3*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int tg3_init_5401phy_dsp (struct tg3*) ; 
 int tg3_phy_auxctl_read (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tg3_phy_auxctl_write (struct tg3*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tg3_phy_copper_an_config_ok (struct tg3*,int*) ; 
 int /*<<< orphan*/  tg3_phy_copper_begin (struct tg3*) ; 
 scalar_t__ tg3_phy_copper_fetch_rmtadv (struct tg3*,int*) ; 
 int /*<<< orphan*/  tg3_phy_eee_adjust (struct tg3*,int) ; 
 int tg3_phy_eee_config_ok (struct tg3*) ; 
 int tg3_phy_reset (struct tg3*) ; 
 scalar_t__ tg3_readphy (struct tg3*,int,int*) ; 
 int /*<<< orphan*/  tg3_setup_eee (struct tg3*) ; 
 int /*<<< orphan*/  tg3_setup_flow_control (struct tg3*,int,int) ; 
 int /*<<< orphan*/  tg3_test_and_report_link_chg (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_write_mem (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_writephy (struct tg3*,int,int) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_setup_copper_phy(struct tg3 *tp, bool force_reset)
{
	bool current_link_up;
	u32 bmsr, val;
	u32 lcl_adv, rmt_adv;
	u32 current_speed;
	u8 current_duplex;
	int i, err;

	tg3_clear_mac_status(tp);

	if ((tp->mi_mode & MAC_MI_MODE_AUTO_POLL) != 0) {
		tw32_f(MAC_MI_MODE,
		     (tp->mi_mode & ~MAC_MI_MODE_AUTO_POLL));
		udelay(80);
	}

	tg3_phy_auxctl_write(tp, MII_TG3_AUXCTL_SHDWSEL_PWRCTL, 0);

	/* Some third-party PHYs need to be reset on link going
	 * down.
	 */
	if ((tg3_asic_rev(tp) == ASIC_REV_5703 ||
	     tg3_asic_rev(tp) == ASIC_REV_5704 ||
	     tg3_asic_rev(tp) == ASIC_REV_5705) &&
	    tp->link_up) {
		tg3_readphy(tp, MII_BMSR, &bmsr);
		if (!tg3_readphy(tp, MII_BMSR, &bmsr) &&
		    !(bmsr & BMSR_LSTATUS))
			force_reset = true;
	}
	if (force_reset)
		tg3_phy_reset(tp);

	if ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5401) {
		tg3_readphy(tp, MII_BMSR, &bmsr);
		if (tg3_readphy(tp, MII_BMSR, &bmsr) ||
		    !tg3_flag(tp, INIT_COMPLETE))
			bmsr = 0;

		if (!(bmsr & BMSR_LSTATUS)) {
			err = tg3_init_5401phy_dsp(tp);
			if (err)
				return err;

			tg3_readphy(tp, MII_BMSR, &bmsr);
			for (i = 0; i < 1000; i++) {
				udelay(10);
				if (!tg3_readphy(tp, MII_BMSR, &bmsr) &&
				    (bmsr & BMSR_LSTATUS)) {
					udelay(40);
					break;
				}
			}

			if ((tp->phy_id & TG3_PHY_ID_REV_MASK) ==
			    TG3_PHY_REV_BCM5401_B0 &&
			    !(bmsr & BMSR_LSTATUS) &&
			    tp->link_config.active_speed == SPEED_1000) {
				err = tg3_phy_reset(tp);
				if (!err)
					err = tg3_init_5401phy_dsp(tp);
				if (err)
					return err;
			}
		}
	} else if (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0 ||
		   tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B0) {
		/* 5701 {A0,B0} CRC bug workaround */
		tg3_writephy(tp, 0x15, 0x0a75);
		tg3_writephy(tp, MII_TG3_MISC_SHDW, 0x8c68);
		tg3_writephy(tp, MII_TG3_MISC_SHDW, 0x8d68);
		tg3_writephy(tp, MII_TG3_MISC_SHDW, 0x8c68);
	}

	/* Clear pending interrupts... */
	tg3_readphy(tp, MII_TG3_ISTAT, &val);
	tg3_readphy(tp, MII_TG3_ISTAT, &val);

	if (tp->phy_flags & TG3_PHYFLG_USE_MI_INTERRUPT)
		tg3_writephy(tp, MII_TG3_IMASK, ~MII_TG3_INT_LINKCHG);
	else if (!(tp->phy_flags & TG3_PHYFLG_IS_FET))
		tg3_writephy(tp, MII_TG3_IMASK, ~0);

	if (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_asic_rev(tp) == ASIC_REV_5701) {
		if (tp->led_ctrl == LED_CTRL_MODE_PHY_1)
			tg3_writephy(tp, MII_TG3_EXT_CTRL,
				     MII_TG3_EXT_CTRL_LNK3_LED_MODE);
		else
			tg3_writephy(tp, MII_TG3_EXT_CTRL, 0);
	}

	current_link_up = false;
	current_speed = SPEED_UNKNOWN;
	current_duplex = DUPLEX_UNKNOWN;
	tp->phy_flags &= ~TG3_PHYFLG_MDIX_STATE;
	tp->link_config.rmt_adv = 0;

	if (tp->phy_flags & TG3_PHYFLG_CAPACITIVE_COUPLING) {
		err = tg3_phy_auxctl_read(tp,
					  MII_TG3_AUXCTL_SHDWSEL_MISCTEST,
					  &val);
		if (!err && !(val & (1 << 10))) {
			tg3_phy_auxctl_write(tp,
					     MII_TG3_AUXCTL_SHDWSEL_MISCTEST,
					     val | (1 << 10));
			goto relink;
		}
	}

	bmsr = 0;
	for (i = 0; i < 100; i++) {
		tg3_readphy(tp, MII_BMSR, &bmsr);
		if (!tg3_readphy(tp, MII_BMSR, &bmsr) &&
		    (bmsr & BMSR_LSTATUS))
			break;
		udelay(40);
	}

	if (bmsr & BMSR_LSTATUS) {
		u32 aux_stat, bmcr;

		tg3_readphy(tp, MII_TG3_AUX_STAT, &aux_stat);
		for (i = 0; i < 2000; i++) {
			udelay(10);
			if (!tg3_readphy(tp, MII_TG3_AUX_STAT, &aux_stat) &&
			    aux_stat)
				break;
		}

		tg3_aux_stat_to_speed_duplex(tp, aux_stat,
					     &current_speed,
					     &current_duplex);

		bmcr = 0;
		for (i = 0; i < 200; i++) {
			tg3_readphy(tp, MII_BMCR, &bmcr);
			if (tg3_readphy(tp, MII_BMCR, &bmcr))
				continue;
			if (bmcr && bmcr != 0x7fff)
				break;
			udelay(10);
		}

		lcl_adv = 0;
		rmt_adv = 0;

		tp->link_config.active_speed = current_speed;
		tp->link_config.active_duplex = current_duplex;

		if (tp->link_config.autoneg == AUTONEG_ENABLE) {
			bool eee_config_ok = tg3_phy_eee_config_ok(tp);

			if ((bmcr & BMCR_ANENABLE) &&
			    eee_config_ok &&
			    tg3_phy_copper_an_config_ok(tp, &lcl_adv) &&
			    tg3_phy_copper_fetch_rmtadv(tp, &rmt_adv))
				current_link_up = true;

			/* EEE settings changes take effect only after a phy
			 * reset.  If we have skipped a reset due to Link Flap
			 * Avoidance being enabled, do it now.
			 */
			if (!eee_config_ok &&
			    (tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN) &&
			    !force_reset) {
				tg3_setup_eee(tp);
				tg3_phy_reset(tp);
			}
		} else {
			if (!(bmcr & BMCR_ANENABLE) &&
			    tp->link_config.speed == current_speed &&
			    tp->link_config.duplex == current_duplex) {
				current_link_up = true;
			}
		}

		if (current_link_up &&
		    tp->link_config.active_duplex == DUPLEX_FULL) {
			u32 reg, bit;

			if (tp->phy_flags & TG3_PHYFLG_IS_FET) {
				reg = MII_TG3_FET_GEN_STAT;
				bit = MII_TG3_FET_GEN_STAT_MDIXSTAT;
			} else {
				reg = MII_TG3_EXT_STAT;
				bit = MII_TG3_EXT_STAT_MDIX;
			}

			if (!tg3_readphy(tp, reg, &val) && (val & bit))
				tp->phy_flags |= TG3_PHYFLG_MDIX_STATE;

			tg3_setup_flow_control(tp, lcl_adv, rmt_adv);
		}
	}

relink:
	if (!current_link_up || (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER)) {
		tg3_phy_copper_begin(tp);

		if (tg3_flag(tp, ROBOSWITCH)) {
			current_link_up = true;
			/* FIXME: when BCM5325 switch is used use 100 MBit/s */
			current_speed = SPEED_1000;
			current_duplex = DUPLEX_FULL;
			tp->link_config.active_speed = current_speed;
			tp->link_config.active_duplex = current_duplex;
		}

		tg3_readphy(tp, MII_BMSR, &bmsr);
		if ((!tg3_readphy(tp, MII_BMSR, &bmsr) && (bmsr & BMSR_LSTATUS)) ||
		    (tp->mac_mode & MAC_MODE_PORT_INT_LPBACK))
			current_link_up = true;
	}

	tp->mac_mode &= ~MAC_MODE_PORT_MODE_MASK;
	if (current_link_up) {
		if (tp->link_config.active_speed == SPEED_100 ||
		    tp->link_config.active_speed == SPEED_10)
			tp->mac_mode |= MAC_MODE_PORT_MODE_MII;
		else
			tp->mac_mode |= MAC_MODE_PORT_MODE_GMII;
	} else if (tp->phy_flags & TG3_PHYFLG_IS_FET)
		tp->mac_mode |= MAC_MODE_PORT_MODE_MII;
	else
		tp->mac_mode |= MAC_MODE_PORT_MODE_GMII;

	/* In order for the 5750 core in BCM4785 chip to work properly
	 * in RGMII mode, the Led Control Register must be set up.
	 */
	if (tg3_flag(tp, RGMII_MODE)) {
		u32 led_ctrl = tr32(MAC_LED_CTRL);
		led_ctrl &= ~(LED_CTRL_1000MBPS_ON | LED_CTRL_100MBPS_ON);

		if (tp->link_config.active_speed == SPEED_10)
			led_ctrl |= LED_CTRL_LNKLED_OVERRIDE;
		else if (tp->link_config.active_speed == SPEED_100)
			led_ctrl |= (LED_CTRL_LNKLED_OVERRIDE |
				     LED_CTRL_100MBPS_ON);
		else if (tp->link_config.active_speed == SPEED_1000)
			led_ctrl |= (LED_CTRL_LNKLED_OVERRIDE |
				     LED_CTRL_1000MBPS_ON);

		tw32(MAC_LED_CTRL, led_ctrl);
		udelay(40);
	}

	tp->mac_mode &= ~MAC_MODE_HALF_DUPLEX;
	if (tp->link_config.active_duplex == DUPLEX_HALF)
		tp->mac_mode |= MAC_MODE_HALF_DUPLEX;

	if (tg3_asic_rev(tp) == ASIC_REV_5700) {
		if (current_link_up &&
		    tg3_5700_link_polarity(tp, tp->link_config.active_speed))
			tp->mac_mode |= MAC_MODE_LINK_POLARITY;
		else
			tp->mac_mode &= ~MAC_MODE_LINK_POLARITY;
	}

	/* ??? Without this setting Netgear GA302T PHY does not
	 * ??? send/receive packets...
	 */
	if ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5411 &&
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5700_ALTIMA) {
		tp->mi_mode |= MAC_MI_MODE_AUTO_POLL;
		tw32_f(MAC_MI_MODE, tp->mi_mode);
		udelay(80);
	}

	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	tg3_phy_eee_adjust(tp, current_link_up);

	if (tg3_flag(tp, USE_LINKCHG_REG)) {
		/* Polled via timer. */
		tw32_f(MAC_EVENT, 0);
	} else {
		tw32_f(MAC_EVENT, MAC_EVENT_LNKSTATE_CHANGED);
	}
	udelay(40);

	if (tg3_asic_rev(tp) == ASIC_REV_5700 &&
	    current_link_up &&
	    tp->link_config.active_speed == SPEED_1000 &&
	    (tg3_flag(tp, PCIX_MODE) || tg3_flag(tp, PCI_HIGH_SPEED))) {
		udelay(120);
		tw32_f(MAC_STATUS,
		     (MAC_STATUS_SYNC_CHANGED |
		      MAC_STATUS_CFG_CHANGED));
		udelay(40);
		tg3_write_mem(tp,
			      NIC_SRAM_FIRMWARE_MBOX,
			      NIC_SRAM_FIRMWARE_MBOX_MAGIC2);
	}

	/* Prevent send BD corruption. */
	if (tg3_flag(tp, CLKREQ_BUG)) {
		if (tp->link_config.active_speed == SPEED_100 ||
		    tp->link_config.active_speed == SPEED_10)
			pcie_capability_clear_word(tp->pdev, PCI_EXP_LNKCTL,
						   PCI_EXP_LNKCTL_CLKREQ_EN);
		else
			pcie_capability_set_word(tp->pdev, PCI_EXP_LNKCTL,
						 PCI_EXP_LNKCTL_CLKREQ_EN);
	}

	tg3_test_and_report_link_chg(tp, current_link_up);

	return 0;
}