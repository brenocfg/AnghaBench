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
struct b43_phy {int rev; int /*<<< orphan*/  radio_rev; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_nphy_channeltab_entry_rev3 {scalar_t__ freq; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct b43_nphy_channeltab_entry_rev3*) ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 struct b43_nphy_channeltab_entry_rev3* b43_nphy_channeltab_phy_rev3 ; 
 struct b43_nphy_channeltab_entry_rev3* b43_nphy_channeltab_phy_rev4 ; 
 struct b43_nphy_channeltab_entry_rev3* b43_nphy_channeltab_radio_rev11 ; 
 struct b43_nphy_channeltab_entry_rev3* b43_nphy_channeltab_radio_rev5 ; 
 struct b43_nphy_channeltab_entry_rev3* b43_nphy_channeltab_radio_rev6 ; 
 struct b43_nphy_channeltab_entry_rev3* b43_nphy_channeltab_radio_rev7_9 ; 
 struct b43_nphy_channeltab_entry_rev3* b43_nphy_channeltab_radio_rev8 ; 

const struct b43_nphy_channeltab_entry_rev3 *
b43_nphy_get_chantabent_rev3(struct b43_wldev *dev, u16 freq)
{
	struct b43_phy *phy = &dev->phy;
	const struct b43_nphy_channeltab_entry_rev3 *e;
	unsigned int length, i;

	switch (phy->rev) {
	case 3:
		e = b43_nphy_channeltab_phy_rev3;
		length = ARRAY_SIZE(b43_nphy_channeltab_phy_rev3);
		break;
	case 4:
		e = b43_nphy_channeltab_phy_rev4;
		length = ARRAY_SIZE(b43_nphy_channeltab_phy_rev4);
		break;
	default:
		switch (phy->radio_rev) {
		case 5:
			e = b43_nphy_channeltab_radio_rev5;
			length = ARRAY_SIZE(b43_nphy_channeltab_radio_rev5);
			break;
		case 6:
			e = b43_nphy_channeltab_radio_rev6;
			length = ARRAY_SIZE(b43_nphy_channeltab_radio_rev6);
			break;
		case 7:
		case 9:
			e = b43_nphy_channeltab_radio_rev7_9;
			length = ARRAY_SIZE(b43_nphy_channeltab_radio_rev7_9);
			break;
		case 8:
			e = b43_nphy_channeltab_radio_rev8;
			length = ARRAY_SIZE(b43_nphy_channeltab_radio_rev8);
			break;
		case 11:
			e = b43_nphy_channeltab_radio_rev11;
			length = ARRAY_SIZE(b43_nphy_channeltab_radio_rev11);
			break;
		default:
			B43_WARN_ON(1);
			return NULL;
		}
	}

	for (i = 0; i < length; i++, e++) {
		if (e->freq == freq)
			return e;
	}

	return NULL;
}