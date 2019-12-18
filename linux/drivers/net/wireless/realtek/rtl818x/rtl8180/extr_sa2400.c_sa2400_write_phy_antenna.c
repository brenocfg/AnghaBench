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
typedef  int /*<<< orphan*/  u8 ;
struct rtl8180_priv {int rfparam; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_ANTATTEN_CHAN14 ; 
 int /*<<< orphan*/  BB_ANTENNA_B ; 
 int RF_PARAM_ANTBDEFAULT ; 
 int /*<<< orphan*/  SA2400_ANTENNA ; 
 int /*<<< orphan*/  rtl8180_write_phy (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sa2400_write_phy_antenna(struct ieee80211_hw *dev, short chan)
{
	struct rtl8180_priv *priv = dev->priv;
	u8 ant = SA2400_ANTENNA;

	if (priv->rfparam & RF_PARAM_ANTBDEFAULT)
		ant |= BB_ANTENNA_B;

	if (chan == 14)
		ant |= BB_ANTATTEN_CHAN14;

	rtl8180_write_phy(dev, 0x10, ant);

}