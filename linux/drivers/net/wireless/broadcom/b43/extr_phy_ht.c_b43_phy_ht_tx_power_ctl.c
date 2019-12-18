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
typedef  int u16 ;
struct TYPE_2__ {struct b43_phy_ht* ht; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
struct b43_phy_ht {int* tx_pwr_idx; int tx_pwr_ctl; } ;

/* Variables and functions */
#define  B43_PHY_HT_TXPCTL_CMD_C1 133 
 int B43_PHY_HT_TXPCTL_CMD_C1_COEFF ; 
 int B43_PHY_HT_TXPCTL_CMD_C1_HWPCTLEN ; 
 int B43_PHY_HT_TXPCTL_CMD_C1_INIT ; 
 int B43_PHY_HT_TXPCTL_CMD_C1_PCTLEN ; 
#define  B43_PHY_HT_TXPCTL_CMD_C2 132 
#define  B43_PHY_HT_TXPCTL_CMD_C3 131 
#define  B43_PHY_HT_TX_PCTL_STATUS_C1 130 
#define  B43_PHY_HT_TX_PCTL_STATUS_C2 129 
#define  B43_PHY_HT_TX_PCTL_STATUS_C3 128 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int const,int) ; 
 int b43_phy_read (struct b43_wldev*,int const) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int const,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int const,int) ; 

__attribute__((used)) static void b43_phy_ht_tx_power_ctl(struct b43_wldev *dev, bool enable)
{
	struct b43_phy_ht *phy_ht = dev->phy.ht;
	u16 en_bits = B43_PHY_HT_TXPCTL_CMD_C1_COEFF |
		      B43_PHY_HT_TXPCTL_CMD_C1_HWPCTLEN |
		      B43_PHY_HT_TXPCTL_CMD_C1_PCTLEN;
	static const u16 cmd_regs[3] = { B43_PHY_HT_TXPCTL_CMD_C1,
					 B43_PHY_HT_TXPCTL_CMD_C2,
					 B43_PHY_HT_TXPCTL_CMD_C3 };
	static const u16 status_regs[3] = { B43_PHY_HT_TX_PCTL_STATUS_C1,
					    B43_PHY_HT_TX_PCTL_STATUS_C2,
					    B43_PHY_HT_TX_PCTL_STATUS_C3 };
	int i;

	if (!enable) {
		if (b43_phy_read(dev, B43_PHY_HT_TXPCTL_CMD_C1) & en_bits) {
			/* We disable enabled TX pwr ctl, save it's state */
			for (i = 0; i < 3; i++)
				phy_ht->tx_pwr_idx[i] =
					b43_phy_read(dev, status_regs[i]);
		}
		b43_phy_mask(dev, B43_PHY_HT_TXPCTL_CMD_C1, ~en_bits);
	} else {
		b43_phy_set(dev, B43_PHY_HT_TXPCTL_CMD_C1, en_bits);

		if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ) {
			for (i = 0; i < 3; i++)
				b43_phy_write(dev, cmd_regs[i], 0x32);
		}

		for (i = 0; i < 3; i++)
			if (phy_ht->tx_pwr_idx[i] <=
			    B43_PHY_HT_TXPCTL_CMD_C1_INIT)
				b43_phy_write(dev, cmd_regs[i],
					      phy_ht->tx_pwr_idx[i]);
	}

	phy_ht->tx_pwr_ctl = enable;
}