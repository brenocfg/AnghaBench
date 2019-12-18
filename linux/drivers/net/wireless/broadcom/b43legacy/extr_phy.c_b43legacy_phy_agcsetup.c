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
struct b43legacy_phy {int rev; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_ilt_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 

__attribute__((used)) static void b43legacy_phy_agcsetup(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 offset = 0x0000;

	if (phy->rev == 1)
		offset = 0x4C00;

	b43legacy_ilt_write(dev, offset, 0x00FE);
	b43legacy_ilt_write(dev, offset + 1, 0x000D);
	b43legacy_ilt_write(dev, offset + 2, 0x0013);
	b43legacy_ilt_write(dev, offset + 3, 0x0019);

	if (phy->rev == 1) {
		b43legacy_ilt_write(dev, 0x1800, 0x2710);
		b43legacy_ilt_write(dev, 0x1801, 0x9B83);
		b43legacy_ilt_write(dev, 0x1802, 0x9B83);
		b43legacy_ilt_write(dev, 0x1803, 0x0F8D);
		b43legacy_phy_write(dev, 0x0455, 0x0004);
	}

	b43legacy_phy_write(dev, 0x04A5, (b43legacy_phy_read(dev, 0x04A5)
					  & 0x00FF) | 0x5700);
	b43legacy_phy_write(dev, 0x041A, (b43legacy_phy_read(dev, 0x041A)
					  & 0xFF80) | 0x000F);
	b43legacy_phy_write(dev, 0x041A, (b43legacy_phy_read(dev, 0x041A)
					  & 0xC07F) | 0x2B80);
	b43legacy_phy_write(dev, 0x048C, (b43legacy_phy_read(dev, 0x048C)
					  & 0xF0FF) | 0x0300);

	b43legacy_radio_write16(dev, 0x007A,
				b43legacy_radio_read16(dev, 0x007A)
				| 0x0008);

	b43legacy_phy_write(dev, 0x04A0, (b43legacy_phy_read(dev, 0x04A0)
			    & 0xFFF0) | 0x0008);
	b43legacy_phy_write(dev, 0x04A1, (b43legacy_phy_read(dev, 0x04A1)
			    & 0xF0FF) | 0x0600);
	b43legacy_phy_write(dev, 0x04A2, (b43legacy_phy_read(dev, 0x04A2)
			    & 0xF0FF) | 0x0700);
	b43legacy_phy_write(dev, 0x04A0, (b43legacy_phy_read(dev, 0x04A0)
			    & 0xF0FF) | 0x0100);

	if (phy->rev == 1)
		b43legacy_phy_write(dev, 0x04A2,
				    (b43legacy_phy_read(dev, 0x04A2)
				    & 0xFFF0) | 0x0007);

	b43legacy_phy_write(dev, 0x0488, (b43legacy_phy_read(dev, 0x0488)
			    & 0xFF00) | 0x001C);
	b43legacy_phy_write(dev, 0x0488, (b43legacy_phy_read(dev, 0x0488)
			    & 0xC0FF) | 0x0200);
	b43legacy_phy_write(dev, 0x0496, (b43legacy_phy_read(dev, 0x0496)
			    & 0xFF00) | 0x001C);
	b43legacy_phy_write(dev, 0x0489, (b43legacy_phy_read(dev, 0x0489)
			    & 0xFF00) | 0x0020);
	b43legacy_phy_write(dev, 0x0489, (b43legacy_phy_read(dev, 0x0489)
			    & 0xC0FF) | 0x0200);
	b43legacy_phy_write(dev, 0x0482, (b43legacy_phy_read(dev, 0x0482)
			    & 0xFF00) | 0x002E);
	b43legacy_phy_write(dev, 0x0496, (b43legacy_phy_read(dev, 0x0496)
			    & 0x00FF) | 0x1A00);
	b43legacy_phy_write(dev, 0x0481, (b43legacy_phy_read(dev, 0x0481)
			    & 0xFF00) | 0x0028);
	b43legacy_phy_write(dev, 0x0481, (b43legacy_phy_read(dev, 0x0481)
			    & 0x00FF) | 0x2C00);

	if (phy->rev == 1) {
		b43legacy_phy_write(dev, 0x0430, 0x092B);
		b43legacy_phy_write(dev, 0x041B,
				    (b43legacy_phy_read(dev, 0x041B)
				    & 0xFFE1) | 0x0002);
	} else {
		b43legacy_phy_write(dev, 0x041B,
				    b43legacy_phy_read(dev, 0x041B) & 0xFFE1);
		b43legacy_phy_write(dev, 0x041F, 0x287A);
		b43legacy_phy_write(dev, 0x0420,
				    (b43legacy_phy_read(dev, 0x0420)
				    & 0xFFF0) | 0x0004);
	}

	if (phy->rev > 2) {
		b43legacy_phy_write(dev, 0x0422, 0x287A);
		b43legacy_phy_write(dev, 0x0420,
				    (b43legacy_phy_read(dev, 0x0420)
				    & 0x0FFF) | 0x3000);
	}

	b43legacy_phy_write(dev, 0x04A8, (b43legacy_phy_read(dev, 0x04A8)
			    & 0x8080) | 0x7874);
	b43legacy_phy_write(dev, 0x048E, 0x1C00);

	if (phy->rev == 1) {
		b43legacy_phy_write(dev, 0x04AB,
				    (b43legacy_phy_read(dev, 0x04AB)
				    & 0xF0FF) | 0x0600);
		b43legacy_phy_write(dev, 0x048B, 0x005E);
		b43legacy_phy_write(dev, 0x048C,
				    (b43legacy_phy_read(dev, 0x048C) & 0xFF00)
				    | 0x001E);
		b43legacy_phy_write(dev, 0x048D, 0x0002);
	}

	b43legacy_ilt_write(dev, offset + 0x0800, 0);
	b43legacy_ilt_write(dev, offset + 0x0801, 7);
	b43legacy_ilt_write(dev, offset + 0x0802, 16);
	b43legacy_ilt_write(dev, offset + 0x0803, 28);

	if (phy->rev >= 6) {
		b43legacy_phy_write(dev, 0x0426,
				    (b43legacy_phy_read(dev, 0x0426) & 0xFFFC));
		b43legacy_phy_write(dev, 0x0426,
				    (b43legacy_phy_read(dev, 0x0426) & 0xEFFF));
	}
}