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
 int /*<<< orphan*/  B43_PHY_N_BMODE (int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nphy_bphy_init(struct b43_wldev *dev)
{
	unsigned int i;
	u16 val;

	val = 0x1E1F;
	for (i = 0; i < 16; i++) {
		b43_phy_write(dev, B43_PHY_N_BMODE(0x88 + i), val);
		val -= 0x202;
	}
	val = 0x3E3F;
	for (i = 0; i < 16; i++) {
		b43_phy_write(dev, B43_PHY_N_BMODE(0x98 + i), val);
		val -= 0x202;
	}
	b43_phy_write(dev, B43_PHY_N_BMODE(0x38), 0x668);
}