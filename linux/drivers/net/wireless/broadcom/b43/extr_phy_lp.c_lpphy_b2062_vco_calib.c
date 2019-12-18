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
 int /*<<< orphan*/  B2062_S_RFPLL_CTL21 ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lpphy_b2062_vco_calib(struct b43_wldev *dev)
{
	b43_radio_write(dev, B2062_S_RFPLL_CTL21, 0x42);
	b43_radio_write(dev, B2062_S_RFPLL_CTL21, 0x62);
	udelay(200);
}