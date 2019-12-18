#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rtl8180_priv {scalar_t__ chip_family; int rx_ring_dma; int /*<<< orphan*/  antenna_diversity_en; int /*<<< orphan*/  antenna_diversity_default; TYPE_2__* rf; TYPE_3__* map; scalar_t__ map_pio; TYPE_1__* tx_ring; int /*<<< orphan*/  anaparam; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rtl8180_priv* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  TX_DMA_POLLING; int /*<<< orphan*/  RF_PARA; int /*<<< orphan*/  RF_TIMING; int /*<<< orphan*/  RFPinsSelect; int /*<<< orphan*/  RFPinsEnable; int /*<<< orphan*/  RFPinsOutput; int /*<<< orphan*/  PGSELECT; int /*<<< orphan*/  CONFIG5; int /*<<< orphan*/  INT_MIG; int /*<<< orphan*/  TID_AC_MAP; int /*<<< orphan*/  ACM_CONTROL; int /*<<< orphan*/  TPPOLL_STOP; int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  CONFIG3; int /*<<< orphan*/  GP_ENABLE; int /*<<< orphan*/  CARRIER_SENSE_COUNTER; int /*<<< orphan*/  PHY_DELAY; int /*<<< orphan*/  SECURITY; int /*<<< orphan*/  RATE_FALLBACK; int /*<<< orphan*/  WPA_CONF; int /*<<< orphan*/  INT_TIMEOUT; int /*<<< orphan*/  CONFIG2; int /*<<< orphan*/  TBKDA; int /*<<< orphan*/  TBEDA; int /*<<< orphan*/  TVIDA; int /*<<< orphan*/  TVODA; int /*<<< orphan*/  TBDA; int /*<<< orphan*/  TLPDA; int /*<<< orphan*/  RDSAR; int /*<<< orphan*/  MSR; int /*<<< orphan*/  CMD; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* init ) (struct ieee80211_hw*) ;} ;
struct TYPE_4__ {int dma; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ARFR ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/ * REG_ADDR1 (int) ; 
 int /*<<< orphan*/ * RFSW_CTRL ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8180 ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8185 ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8187SE ; 
 int RTL818X_CMD_RESET ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_LOAD ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int RTL818X_MSR_ENEDCA ; 
 int RTL818x_TPPOLL_STOP_HI ; 
 int RTL818x_TPPOLL_STOP_MG ; 
 int /*<<< orphan*/  RTL8225SE_ANAPARAM2_ON ; 
 int /*<<< orphan*/  RTL8225SE_ANAPARAM3 ; 
 int /*<<< orphan*/  RTL8225SE_ANAPARAM_ON ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtl8180_conf_basic_rates (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8180_config_cardbus (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8180_int_disable (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8180_set_anaparam (struct rtl8180_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_set_anaparam2 (struct rtl8180_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_set_anaparam3 (struct rtl8180_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8187se_mac_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8187se_set_antenna_config (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl818x_ioread16 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int rtl818x_ioread32 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rtl8180_init_hw(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;
	u16 reg;
	u32 reg32;

	rtl818x_iowrite8(priv, &priv->map->CMD, 0);
	rtl818x_ioread8(priv, &priv->map->CMD);
	msleep(10);

	/* reset */
	rtl8180_int_disable(dev);
	rtl818x_ioread8(priv, &priv->map->CMD);

	reg = rtl818x_ioread8(priv, &priv->map->CMD);
	reg &= (1 << 1);
	reg |= RTL818X_CMD_RESET;
	rtl818x_iowrite8(priv, &priv->map->CMD, RTL818X_CMD_RESET);
	rtl818x_ioread8(priv, &priv->map->CMD);
	msleep(200);

	/* check success of reset */
	if (rtl818x_ioread8(priv, &priv->map->CMD) & RTL818X_CMD_RESET) {
		wiphy_err(dev->wiphy, "reset timeout!\n");
		return -ETIMEDOUT;
	}

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_LOAD);
	rtl818x_ioread8(priv, &priv->map->CMD);
	msleep(200);

	if (rtl818x_ioread8(priv, &priv->map->CONFIG3) & (1 << 3)) {
		rtl8180_config_cardbus(dev);
	}

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		rtl818x_iowrite8(priv, &priv->map->MSR, RTL818X_MSR_ENEDCA);
	else
		rtl818x_iowrite8(priv, &priv->map->MSR, 0);

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180)
		rtl8180_set_anaparam(priv, priv->anaparam);

	rtl818x_iowrite32(priv, &priv->map->RDSAR, priv->rx_ring_dma);
	/* mac80211 queue have higher prio for lower index. The last queue
	 * (that mac80211 is not aware of) is reserved for beacons (and have
	 * the highest priority on the NIC)
	 */
	if (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8187SE) {
		rtl818x_iowrite32(priv, &priv->map->TBDA,
				  priv->tx_ring[1].dma);
		rtl818x_iowrite32(priv, &priv->map->TLPDA,
				  priv->tx_ring[0].dma);
	} else {
		rtl818x_iowrite32(priv, &priv->map->TBDA,
				  priv->tx_ring[4].dma);
		rtl818x_iowrite32(priv, &priv->map->TVODA,
				  priv->tx_ring[0].dma);
		rtl818x_iowrite32(priv, &priv->map->TVIDA,
				  priv->tx_ring[1].dma);
		rtl818x_iowrite32(priv, &priv->map->TBEDA,
				  priv->tx_ring[2].dma);
		rtl818x_iowrite32(priv, &priv->map->TBKDA,
				  priv->tx_ring[3].dma);
	}

	/* TODO: necessary? specs indicate not */
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG2);
	rtl818x_iowrite8(priv, &priv->map->CONFIG2, reg & ~(1 << 3));
	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8185) {
		reg = rtl818x_ioread8(priv, &priv->map->CONFIG2);
		rtl818x_iowrite8(priv, &priv->map->CONFIG2, reg | (1 << 4));
	}
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	/* TODO: set CONFIG5 for calibrating AGC on rtl8180 + philips radio? */

	/* TODO: turn off hw wep on rtl8180 */

	rtl818x_iowrite32(priv, &priv->map->INT_TIMEOUT, 0);

	if (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180) {
		rtl818x_iowrite8(priv, &priv->map->WPA_CONF, 0);
		rtl818x_iowrite8(priv, &priv->map->RATE_FALLBACK, 0);
	} else {
		rtl818x_iowrite8(priv, &priv->map->SECURITY, 0);

		rtl818x_iowrite8(priv, &priv->map->PHY_DELAY, 0x6);
		rtl818x_iowrite8(priv, &priv->map->CARRIER_SENSE_COUNTER, 0x4C);
	}

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8185) {
		/* TODO: set ClkRun enable? necessary? */
		reg = rtl818x_ioread8(priv, &priv->map->GP_ENABLE);
		rtl818x_iowrite8(priv, &priv->map->GP_ENABLE, reg & ~(1 << 6));
		rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
		reg = rtl818x_ioread8(priv, &priv->map->CONFIG3);
		rtl818x_iowrite8(priv, &priv->map->CONFIG3, reg | (1 << 2));
		rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);
		/* fix eccessive IFS after CTS-to-self */
		if (priv->map_pio) {
			u8 reg;

			reg = rtl818x_ioread8(priv, &priv->map->PGSELECT);
			rtl818x_iowrite8(priv, &priv->map->PGSELECT, reg | 1);
			rtl818x_iowrite8(priv, REG_ADDR1(0xff), 0x35);
			rtl818x_iowrite8(priv, &priv->map->PGSELECT, reg);
		} else
			rtl818x_iowrite8(priv, REG_ADDR1(0x1ff), 0x35);
	}

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) {

		/* the set auto rate fallback bitmask from 1M to 54 Mb/s */
		rtl818x_iowrite16(priv, ARFR, 0xFFF);
		rtl818x_ioread16(priv, ARFR);

		/* stop unused queus (no dma alloc) */
		rtl818x_iowrite8(priv, &priv->map->TPPOLL_STOP,
			       RTL818x_TPPOLL_STOP_MG | RTL818x_TPPOLL_STOP_HI);

		rtl818x_iowrite8(priv, &priv->map->ACM_CONTROL, 0x00);
		rtl818x_iowrite16(priv, &priv->map->TID_AC_MAP, 0xFA50);

		rtl818x_iowrite16(priv, &priv->map->INT_MIG, 0);

		/* some black magic here.. */
		rtl8187se_mac_config(dev);

		rtl818x_iowrite16(priv, RFSW_CTRL, 0x569A);
		rtl818x_ioread16(priv, RFSW_CTRL);

		rtl8180_set_anaparam(priv, RTL8225SE_ANAPARAM_ON);
		rtl8180_set_anaparam2(priv, RTL8225SE_ANAPARAM2_ON);
		rtl8180_set_anaparam3(priv, RTL8225SE_ANAPARAM3);


		rtl818x_iowrite8(priv, &priv->map->CONFIG5,
			    rtl818x_ioread8(priv, &priv->map->CONFIG5) & 0x7F);

		/*probably this switch led on */
		rtl818x_iowrite8(priv, &priv->map->PGSELECT,
			    rtl818x_ioread8(priv, &priv->map->PGSELECT) | 0x08);

		rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, 0x0480);
		rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, 0x1BFF);
		rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, 0x2488);

		rtl818x_iowrite32(priv, &priv->map->RF_TIMING, 0x4003);

		/* the reference code mac hardcode table write
		 * this reg by doing byte-wide accesses.
		 * It does it just for lowest and highest byte..
		 */
		reg32 = rtl818x_ioread32(priv, &priv->map->RF_PARA);
		reg32 &= 0x00ffff00;
		reg32 |= 0xb8000054;
		rtl818x_iowrite32(priv, &priv->map->RF_PARA, reg32);
	} else
		/* stop unused queus (no dma alloc) */
		rtl818x_iowrite8(priv, &priv->map->TX_DMA_POLLING,
			    (1<<1) | (1<<2));

	priv->rf->init(dev);

	/* default basic rates are 1,2 Mbps for rtl8180. 1,2,6,9,12,18,24 Mbps
	 * otherwise. bitmask 0x3 and 0x01f3 respectively.
	 * NOTE: currenty rtl8225 RF code changes basic rates, so we need to do
	 * this after rf init.
	 * TODO: try to find out whether RF code really needs to do this..
	 */
	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180)
		rtl8180_conf_basic_rates(dev, 0x3);
	else
		rtl8180_conf_basic_rates(dev, 0x1f3);

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		rtl8187se_set_antenna_config(dev,
					     priv->antenna_diversity_default,
					     priv->antenna_diversity_en);
	return 0;
}