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
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2062_N_COMM1 ; 
 int /*<<< orphan*/  B2062_S_RFPLL_CTL2 ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lpphy_b2062_reset_pll_bias(struct b43_wldev *dev)
{
	b43_radio_write(dev, B2062_S_RFPLL_CTL2, 0xFF);
	udelay(20);
	if (dev->dev->chip_id == 0x5354) {
		b43_radio_write(dev, B2062_N_COMM1, 4);
		b43_radio_write(dev, B2062_S_RFPLL_CTL2, 4);
	} else {
		b43_radio_write(dev, B2062_S_RFPLL_CTL2, 0);
	}
	udelay(5);
}