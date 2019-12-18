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
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_ht {scalar_t__* bb_mult_save; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_HTTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_PHY_HT_IQLOCAL_CMDGCTL ; 
 int /*<<< orphan*/  B43_PHY_HT_SAMP_CMD ; 
 int /*<<< orphan*/  B43_PHY_HT_SAMP_CMD_STOP ; 
 int /*<<< orphan*/  B43_PHY_HT_SAMP_STAT ; 
 int /*<<< orphan*/  b43_httab_write (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_phy_ht_stop_playback(struct b43_wldev *dev)
{
	struct b43_phy_ht *phy_ht = dev->phy.ht;
	u16 tmp;
	int i;

	tmp = b43_phy_read(dev, B43_PHY_HT_SAMP_STAT);
	if (tmp & 0x1)
		b43_phy_set(dev, B43_PHY_HT_SAMP_CMD, B43_PHY_HT_SAMP_CMD_STOP);
	else if (tmp & 0x2)
		b43_phy_mask(dev, B43_PHY_HT_IQLOCAL_CMDGCTL, 0x7FFF);

	b43_phy_mask(dev, B43_PHY_HT_SAMP_CMD, ~0x0004);

	for (i = 0; i < 3; i++) {
		if (phy_ht->bb_mult_save[i] >= 0) {
			b43_httab_write(dev, B43_HTTAB16(13, 0x63 + i * 4),
					phy_ht->bb_mult_save[i]);
			b43_httab_write(dev, B43_HTTAB16(13, 0x67 + i * 4),
					phy_ht->bb_mult_save[i]);
		}
	}
}