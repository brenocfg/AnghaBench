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
typedef  int u8 ;
struct rtl8180_priv {scalar_t__ chip_family; int slot_time; int ack_time; TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct ieee80211_bss_conf {scalar_t__ use_short_slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  EIFS; int /*<<< orphan*/  EIFS_8187SE; int /*<<< orphan*/  CARRIER_SENSE_COUNTER; int /*<<< orphan*/  DIFS; int /*<<< orphan*/  SIFS; int /*<<< orphan*/  SLOT; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8180 ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8185 ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8187SE ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rtl8180_conf_erp(struct ieee80211_hw *dev,
			    struct ieee80211_bss_conf *info)
{
	struct rtl8180_priv *priv = dev->priv;
	u8 sifs, difs;
	int eifs;
	u8 hw_eifs;

	/* TODO: should we do something ? */
	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180)
		return;

	/* I _hope_ this means 10uS for the HW.
	 * In reference code it is 0x22 for
	 * both rtl8187L and rtl8187SE
	 */
	sifs = 0x22;

	if (info->use_short_slot)
		priv->slot_time = 9;
	else
		priv->slot_time = 20;

	/* 10 is SIFS time in uS */
	difs = 10 + 2 * priv->slot_time;
	eifs = 10 + difs + priv->ack_time;

	/* HW should use 4uS units for EIFS (I'm sure for rtl8185)*/
	hw_eifs = DIV_ROUND_UP(eifs, 4);


	rtl818x_iowrite8(priv, &priv->map->SLOT, priv->slot_time);
	rtl818x_iowrite8(priv, &priv->map->SIFS, sifs);
	rtl818x_iowrite8(priv, &priv->map->DIFS, difs);

	/* from reference code. set ack timeout reg = eifs reg */
	rtl818x_iowrite8(priv, &priv->map->CARRIER_SENSE_COUNTER, hw_eifs);

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		rtl818x_iowrite8(priv, &priv->map->EIFS_8187SE, hw_eifs);
	else if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8185) {
		/* rtl8187/rtl8185 HW bug. After EIFS is elapsed,
		 * the HW still wait for DIFS.
		 * HW uses 4uS units for EIFS.
		 */
		hw_eifs = DIV_ROUND_UP(eifs - difs, 4);

		rtl818x_iowrite8(priv, &priv->map->EIFS, hw_eifs);
	}
}