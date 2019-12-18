#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct b43legacy_wldev {TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {int boardflags_lo; } ;
struct TYPE_5__ {TYPE_1__ sprom; } ;

/* Variables and functions */
 int B43legacy_BFL_RSSI ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_slope (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_mac_enable (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_mac_suspend (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_mark_all_unused (struct b43legacy_wldev*) ; 

__attribute__((used)) static void b43legacy_periodic_every60sec(struct b43legacy_wldev *dev)
{
	b43legacy_phy_lo_mark_all_unused(dev);
	if (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_RSSI) {
		b43legacy_mac_suspend(dev);
		b43legacy_calc_nrssi_slope(dev);
		b43legacy_mac_enable(dev);
	}
}