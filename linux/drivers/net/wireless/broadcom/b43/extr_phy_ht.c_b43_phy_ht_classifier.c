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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_HT_CLASS_CTL ; 
 int B43_PHY_HT_CLASS_CTL_CCK_EN ; 
 int B43_PHY_HT_CLASS_CTL_OFDM_EN ; 
 int B43_PHY_HT_CLASS_CTL_WAITED_EN ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 b43_phy_ht_classifier(struct b43_wldev *dev, u16 mask, u16 val)
{
	u16 tmp;
	u16 allowed = B43_PHY_HT_CLASS_CTL_CCK_EN |
		      B43_PHY_HT_CLASS_CTL_OFDM_EN |
		      B43_PHY_HT_CLASS_CTL_WAITED_EN;

	tmp = b43_phy_read(dev, B43_PHY_HT_CLASS_CTL);
	tmp &= allowed;
	tmp &= ~mask;
	tmp |= (val & mask);
	b43_phy_maskset(dev, B43_PHY_HT_CLASS_CTL, ~allowed, tmp);

	return tmp;
}