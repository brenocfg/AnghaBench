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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {struct b43_phy_ht* ht; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_ht {int* rf_ctl_int_save; } ;

/* Variables and functions */
#define  B43_PHY_HT_RF_CTL_INT_C1 130 
#define  B43_PHY_HT_RF_CTL_INT_C2 129 
#define  B43_PHY_HT_RF_CTL_INT_C3 128 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void b43_phy_ht_pa_override(struct b43_wldev *dev, bool enable)
{
	struct b43_phy_ht *htphy = dev->phy.ht;
	static const u16 regs[3] = { B43_PHY_HT_RF_CTL_INT_C1,
				     B43_PHY_HT_RF_CTL_INT_C2,
				     B43_PHY_HT_RF_CTL_INT_C3 };
	int i;

	if (enable) {
		for (i = 0; i < 3; i++)
			b43_phy_write(dev, regs[i], htphy->rf_ctl_int_save[i]);
	} else {
		for (i = 0; i < 3; i++)
			htphy->rf_ctl_int_save[i] = b43_phy_read(dev, regs[i]);
		/* TODO: Does 5GHz band use different value (not 0x0400)? */
		for (i = 0; i < 3; i++)
			b43_phy_write(dev, regs[i], 0x0400);
	}
}