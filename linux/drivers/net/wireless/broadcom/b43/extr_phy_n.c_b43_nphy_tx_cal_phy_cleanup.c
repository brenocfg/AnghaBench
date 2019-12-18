#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int rev; TYPE_1__* n; } ;
struct b43_wldev {TYPE_2__ phy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tx_rx_cal_phy_saveregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_AFECTL_C1 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_C2 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  B43_NPHY_BBCFG ; 
 int /*<<< orphan*/  B43_NPHY_PAPD_EN0 ; 
 int /*<<< orphan*/  B43_NPHY_PAPD_EN1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC2 ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 int /*<<< orphan*/  b43_nphy_reset_cca (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_nphy_tx_cal_phy_cleanup(struct b43_wldev *dev)
{
	u16 *regs = dev->phy.n->tx_rx_cal_phy_saveregs;

	if (dev->phy.rev >= 3) {
		b43_phy_write(dev, B43_NPHY_AFECTL_C1, regs[0]);
		b43_phy_write(dev, B43_NPHY_AFECTL_C2, regs[1]);
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER1, regs[2]);
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER, regs[3]);
		b43_phy_write(dev, B43_NPHY_BBCFG, regs[4]);
		b43_ntab_write(dev, B43_NTAB16(8, 3), regs[5]);
		b43_ntab_write(dev, B43_NTAB16(8, 19), regs[6]);
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC1, regs[7]);
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC2, regs[8]);
		b43_phy_write(dev, B43_NPHY_PAPD_EN0, regs[9]);
		b43_phy_write(dev, B43_NPHY_PAPD_EN1, regs[10]);
		b43_nphy_reset_cca(dev);
	} else {
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C1, 0x0FFF, regs[0]);
		b43_phy_maskset(dev, B43_NPHY_AFECTL_C2, 0x0FFF, regs[1]);
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER, regs[2]);
		b43_ntab_write(dev, B43_NTAB16(8, 2), regs[3]);
		b43_ntab_write(dev, B43_NTAB16(8, 18), regs[4]);
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC1, regs[5]);
		b43_phy_write(dev, B43_NPHY_RFCTL_INTC2, regs[6]);
	}
}