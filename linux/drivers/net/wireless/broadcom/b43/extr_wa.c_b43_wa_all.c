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
struct b43_phy {scalar_t__ type; int rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_wa_altagc (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_analog (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_art (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_boards_g (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_cck_shiftbits (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_cpll_nonpilot (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_crs_blank (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_crs_ed (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_crs_thr (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_fft (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_msst (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_nft (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_nst (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_rssi_lt (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_rt (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_tr_ltov (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_txpuoff_rxpuon (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_wrssi_offset (struct b43_wldev*) ; 

void b43_wa_all(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	if (phy->type == B43_PHYTYPE_G) {
		switch (phy->rev) {
		case 1://XXX review rev1
			b43_wa_crs_ed(dev);
			b43_wa_crs_thr(dev);
			b43_wa_crs_blank(dev);
			b43_wa_cck_shiftbits(dev);
			b43_wa_fft(dev);
			b43_wa_nft(dev);
			b43_wa_rt(dev);
			b43_wa_nst(dev);
			b43_wa_art(dev);
			b43_wa_wrssi_offset(dev);
			b43_wa_altagc(dev);
			break;
		case 2:
		case 6:
		case 7:
		case 8:
		case 9:
			b43_wa_tr_ltov(dev);
			b43_wa_crs_ed(dev);
			b43_wa_rssi_lt(dev);
			b43_wa_nft(dev);
			b43_wa_nst(dev);
			b43_wa_msst(dev);
			b43_wa_wrssi_offset(dev);
			b43_wa_altagc(dev);
			b43_wa_analog(dev);
			b43_wa_txpuoff_rxpuon(dev);
			break;
		default:
			B43_WARN_ON(1);
		}
		b43_wa_boards_g(dev);
	} else { /* No N PHY support so far, LP PHY is in phy_lp.c */
		B43_WARN_ON(1);
	}

	b43_wa_cpll_nonpilot(dev);
}