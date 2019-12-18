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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_PS_CTL_OVERRIDE_VAL0 ; 
 int /*<<< orphan*/  B43_LPPHY_PS_CTL_OVERRIDE_VAL1 ; 
 int /*<<< orphan*/  B43_LPPHY_PS_CTL_OVERRIDE_VAL2 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2_VAL ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_VAL_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RX_GAIN_CTL_OVERRIDE_VAL ; 
 int /*<<< orphan*/  B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpphy_set_deaf (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_trsw_over (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void lpphy_disable_crs(struct b43_wldev *dev, bool user)
{
	lpphy_set_deaf(dev, user);
	lpphy_set_trsw_over(dev, false, true);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFFB);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x4);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFF7);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x8);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0x10);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x10);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFDF);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x20);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFBF);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x40);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0x7);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0x38);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFF3F);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0x100);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFDFF);
	b43_phy_write(dev, B43_LPPHY_PS_CTL_OVERRIDE_VAL0, 0);
	b43_phy_write(dev, B43_LPPHY_PS_CTL_OVERRIDE_VAL1, 1);
	b43_phy_write(dev, B43_LPPHY_PS_CTL_OVERRIDE_VAL2, 0x20);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xFBFF);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2_VAL, 0xF7FF);
	b43_phy_write(dev, B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL, 0);
	b43_phy_write(dev, B43_LPPHY_RX_GAIN_CTL_OVERRIDE_VAL, 0x45AF);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_2, 0x3FF);
}