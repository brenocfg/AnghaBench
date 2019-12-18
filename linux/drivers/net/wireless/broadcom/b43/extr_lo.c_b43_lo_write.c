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
typedef  int u8 ;
typedef  int u16 ;
struct b43_phy {scalar_t__ type; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
struct b43_loctl {scalar_t__ i; scalar_t__ q; } ;

/* Variables and functions */
 scalar_t__ B43_DEBUG ; 
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_PHY_LO_CTL ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void b43_lo_write(struct b43_wldev *dev, struct b43_loctl *control)
{
	struct b43_phy *phy = &dev->phy;
	u16 value;

	if (B43_DEBUG) {
		if (unlikely(abs(control->i) > 16 || abs(control->q) > 16)) {
			b43dbg(dev->wl, "Invalid LO control pair "
			       "(I: %d, Q: %d)\n", control->i, control->q);
			dump_stack();
			return;
		}
	}
	B43_WARN_ON(phy->type != B43_PHYTYPE_G);

	value = (u8) (control->q);
	value |= ((u8) (control->i)) << 8;
	b43_phy_write(dev, B43_PHY_LO_CTL, value);
}