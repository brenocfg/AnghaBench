#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct nphy_gain_ctl_workaround_entry {int cliplo_gain; int* rfseq_init; int init_gain; int crsminu; } ;
struct b43_phy {int rev; int radio_rev; } ;
struct b43_wldev {TYPE_4__* dev; struct b43_phy phy; } ;
struct TYPE_8__ {TYPE_3__* bus_sprom; } ;
struct TYPE_5__ {size_t tr_iso; } ;
struct TYPE_6__ {TYPE_1__ ghz2; } ;
struct TYPE_7__ {TYPE_2__ fem; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_is_40mhz (struct b43_wldev*) ; 
 struct nphy_gain_ctl_workaround_entry nphy_gain_ctl_wa_phy6_radio11_ghz2 ; 
 struct nphy_gain_ctl_workaround_entry** nphy_gain_ctl_workaround ; 

struct nphy_gain_ctl_workaround_entry *b43_nphy_get_gain_ctl_workaround_ent(
	struct b43_wldev *dev, bool ghz5, bool ext_lna)
{
	struct b43_phy *phy = &dev->phy;
	struct nphy_gain_ctl_workaround_entry *e;
	u8 phy_idx;

	if (!ghz5 && dev->phy.rev >= 6 && dev->phy.radio_rev == 11)
		return &nphy_gain_ctl_wa_phy6_radio11_ghz2;

	B43_WARN_ON(dev->phy.rev < 3);
	if (dev->phy.rev >= 6)
		phy_idx = 3;
	else if (dev->phy.rev == 5)
		phy_idx = 2;
	else if (dev->phy.rev == 4)
		phy_idx = 1;
	else
		phy_idx = 0;
	e = &nphy_gain_ctl_workaround[ghz5][phy_idx];

	/* Some workarounds to the workarounds... */
	if (!ghz5) {
		u8 tr_iso = dev->dev->bus_sprom->fem.ghz2.tr_iso;

		if (tr_iso > 7)
			tr_iso = 3;

		if (phy->rev >= 6) {
			static const int gain_data[] = { 0x106a, 0x106c, 0x1074,
							 0x107c, 0x007e, 0x107e,
							 0x207e, 0x307e, };

			e->cliplo_gain = gain_data[tr_iso];
		} else if (phy->rev == 5) {
			static const int gain_data[] = { 0x0062, 0x0064, 0x006a,
							 0x106a, 0x106c, 0x1074,
							 0x107c, 0x207c, };

			e->cliplo_gain = gain_data[tr_iso];
		}

		if (phy->rev >= 5 && ext_lna) {
			e->rfseq_init[0] &= ~0x4000;
			e->rfseq_init[1] &= ~0x4000;
			e->rfseq_init[2] &= ~0x4000;
			e->rfseq_init[3] &= ~0x4000;
			e->init_gain &= ~0x4000;
		}
	} else {
		if (phy->rev >= 6) {
			if (phy->radio_rev == 11 && !b43_is_40mhz(dev))
				e->crsminu = 0x2d;
		} else if (phy->rev == 4 && ext_lna) {
			e->rfseq_init[0] &= ~0x4000;
			e->rfseq_init[1] &= ~0x4000;
			e->rfseq_init[2] &= ~0x4000;
			e->rfseq_init[3] &= ~0x4000;
			e->init_gain &= ~0x4000;
			e->rfseq_init[0] |= 0x1000;
			e->rfseq_init[1] |= 0x1000;
			e->rfseq_init[2] |= 0x1000;
			e->rfseq_init[3] |= 0x1000;
			e->init_gain |= 0x1000;
		}
	}

	return e;
}