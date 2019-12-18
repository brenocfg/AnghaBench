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
typedef  scalar_t__ u16 ;
struct b43_phy {int rev; int radio_rev; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_nphy_chantabent_rev7_2g {scalar_t__ freq; } ;
struct b43_nphy_chantabent_rev7 {scalar_t__ freq; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 void* b43_nphy_chantab_phy_rev16_radio_rev9 ; 
 void* b43_nphy_chantab_phy_rev17_radio_rev14 ; 
 void* b43_nphy_chantab_phy_rev8_radio_rev5 ; 

void r2057_get_chantabent_rev7(struct b43_wldev *dev, u16 freq,
			       const struct b43_nphy_chantabent_rev7 **tabent_r7,
			       const struct b43_nphy_chantabent_rev7_2g **tabent_r7_2g)
{
	struct b43_phy *phy = &dev->phy;
	const struct b43_nphy_chantabent_rev7 *e_r7 = NULL;
	const struct b43_nphy_chantabent_rev7_2g *e_r7_2g = NULL;
	unsigned int len, i;

	*tabent_r7 = NULL;
	*tabent_r7_2g = NULL;

	switch (phy->rev) {
	case 8:
		if (phy->radio_rev == 5) {
			e_r7_2g = b43_nphy_chantab_phy_rev8_radio_rev5;
			len = ARRAY_SIZE(b43_nphy_chantab_phy_rev8_radio_rev5);
		}
		break;
	case 16:
		if (phy->radio_rev == 9) {
			e_r7 = b43_nphy_chantab_phy_rev16_radio_rev9;
			len = ARRAY_SIZE(b43_nphy_chantab_phy_rev16_radio_rev9);
		}
		break;
	case 17:
		if (phy->radio_rev == 14) {
			e_r7_2g = b43_nphy_chantab_phy_rev17_radio_rev14;
			len = ARRAY_SIZE(b43_nphy_chantab_phy_rev17_radio_rev14);
		}
		break;
	default:
		break;
	}

	if (e_r7) {
		for (i = 0; i < len; i++, e_r7++) {
			if (e_r7->freq == freq) {
				*tabent_r7 = e_r7;
				return;
			}
		}
	} else if (e_r7_2g) {
		for (i = 0; i < len; i++, e_r7_2g++) {
			if (e_r7_2g->freq == freq) {
				*tabent_r7_2g = e_r7_2g;
				return;
			}
		}
	} else {
		B43_WARN_ON(1);
	}
}