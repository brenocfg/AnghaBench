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
struct rtl8180_priv {scalar_t__ chip_family; TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  INT_MASK; int /*<<< orphan*/  IMR; } ;

/* Variables and functions */
 int IMR_RDU ; 
 int IMR_RER ; 
 int IMR_ROK ; 
 int IMR_RQOSOK ; 
 int IMR_TBDER ; 
 int IMR_TBDOK ; 
 int IMR_TBEDER ; 
 int IMR_TBEDOK ; 
 int IMR_TBKDER ; 
 int IMR_TBKDOK ; 
 int IMR_TVIDER ; 
 int IMR_TVIDOK ; 
 int IMR_TVODER ; 
 int IMR_TVODOK ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8187SE ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rtl8180_int_enable(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) {
		rtl818x_iowrite32(priv, &priv->map->IMR,
			  IMR_TBDER | IMR_TBDOK |
			  IMR_TVODER | IMR_TVODOK |
			  IMR_TVIDER | IMR_TVIDOK |
			  IMR_TBEDER | IMR_TBEDOK |
			  IMR_TBKDER | IMR_TBKDOK |
			  IMR_RDU | IMR_RER |
			  IMR_ROK | IMR_RQOSOK);
	} else {
		rtl818x_iowrite16(priv, &priv->map->INT_MASK, 0xFFFF);
	}
}