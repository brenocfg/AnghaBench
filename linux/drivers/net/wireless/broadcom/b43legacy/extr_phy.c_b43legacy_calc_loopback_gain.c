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
typedef  int u16 ;
struct b43legacy_phy {int rev; int bbatt; scalar_t__ analog; int radio_ver; int radio_rev; int* loopback_gain; } ;
struct b43legacy_wldev {TYPE_3__* dev; struct b43legacy_phy phy; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {int boardflags_lo; } ;
struct TYPE_5__ {TYPE_1__ sprom; } ;

/* Variables and functions */
 int B43legacy_BFL_EXTLNA ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_set_baseband_attenuation (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43legacy_calc_loopback_gain(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 backup_phy[15] = {0};
	u16 backup_radio[3];
	u16 backup_bband;
	u16 i;
	u16 loop1_cnt;
	u16 loop1_done;
	u16 loop1_omitted;
	u16 loop2_done;

	backup_phy[0] = b43legacy_phy_read(dev, 0x0429);
	backup_phy[1] = b43legacy_phy_read(dev, 0x0001);
	backup_phy[2] = b43legacy_phy_read(dev, 0x0811);
	backup_phy[3] = b43legacy_phy_read(dev, 0x0812);
	if (phy->rev != 1) {
		backup_phy[4] = b43legacy_phy_read(dev, 0x0814);
		backup_phy[5] = b43legacy_phy_read(dev, 0x0815);
	}
	backup_phy[6] = b43legacy_phy_read(dev, 0x005A);
	backup_phy[7] = b43legacy_phy_read(dev, 0x0059);
	backup_phy[8] = b43legacy_phy_read(dev, 0x0058);
	backup_phy[9] = b43legacy_phy_read(dev, 0x000A);
	backup_phy[10] = b43legacy_phy_read(dev, 0x0003);
	backup_phy[11] = b43legacy_phy_read(dev, 0x080F);
	backup_phy[12] = b43legacy_phy_read(dev, 0x0810);
	backup_phy[13] = b43legacy_phy_read(dev, 0x002B);
	backup_phy[14] = b43legacy_phy_read(dev, 0x0015);
	b43legacy_phy_read(dev, 0x002D); /* dummy read */
	backup_bband = phy->bbatt;
	backup_radio[0] = b43legacy_radio_read16(dev, 0x0052);
	backup_radio[1] = b43legacy_radio_read16(dev, 0x0043);
	backup_radio[2] = b43legacy_radio_read16(dev, 0x007A);

	b43legacy_phy_write(dev, 0x0429,
			    b43legacy_phy_read(dev, 0x0429) & 0x3FFF);
	b43legacy_phy_write(dev, 0x0001,
			    b43legacy_phy_read(dev, 0x0001) & 0x8000);
	b43legacy_phy_write(dev, 0x0811,
			    b43legacy_phy_read(dev, 0x0811) | 0x0002);
	b43legacy_phy_write(dev, 0x0812,
			    b43legacy_phy_read(dev, 0x0812) & 0xFFFD);
	b43legacy_phy_write(dev, 0x0811,
			    b43legacy_phy_read(dev, 0x0811) | 0x0001);
	b43legacy_phy_write(dev, 0x0812,
			    b43legacy_phy_read(dev, 0x0812) & 0xFFFE);
	if (phy->rev != 1) {
		b43legacy_phy_write(dev, 0x0814,
				    b43legacy_phy_read(dev, 0x0814) | 0x0001);
		b43legacy_phy_write(dev, 0x0815,
				    b43legacy_phy_read(dev, 0x0815) & 0xFFFE);
		b43legacy_phy_write(dev, 0x0814,
				    b43legacy_phy_read(dev, 0x0814) | 0x0002);
		b43legacy_phy_write(dev, 0x0815,
				    b43legacy_phy_read(dev, 0x0815) & 0xFFFD);
	}
	b43legacy_phy_write(dev, 0x0811, b43legacy_phy_read(dev, 0x0811) |
			    0x000C);
	b43legacy_phy_write(dev, 0x0812, b43legacy_phy_read(dev, 0x0812) |
			    0x000C);

	b43legacy_phy_write(dev, 0x0811, (b43legacy_phy_read(dev, 0x0811)
			    & 0xFFCF) | 0x0030);
	b43legacy_phy_write(dev, 0x0812, (b43legacy_phy_read(dev, 0x0812)
			    & 0xFFCF) | 0x0010);

	b43legacy_phy_write(dev, 0x005A, 0x0780);
	b43legacy_phy_write(dev, 0x0059, 0xC810);
	b43legacy_phy_write(dev, 0x0058, 0x000D);
	if (phy->analog == 0)
		b43legacy_phy_write(dev, 0x0003, 0x0122);
	else
		b43legacy_phy_write(dev, 0x000A,
				    b43legacy_phy_read(dev, 0x000A)
				    | 0x2000);
	if (phy->rev != 1) {
		b43legacy_phy_write(dev, 0x0814,
				    b43legacy_phy_read(dev, 0x0814) | 0x0004);
		b43legacy_phy_write(dev, 0x0815,
				    b43legacy_phy_read(dev, 0x0815) & 0xFFFB);
	}
	b43legacy_phy_write(dev, 0x0003,
			    (b43legacy_phy_read(dev, 0x0003)
			     & 0xFF9F) | 0x0040);
	if (phy->radio_ver == 0x2050 && phy->radio_rev == 2) {
		b43legacy_radio_write16(dev, 0x0052, 0x0000);
		b43legacy_radio_write16(dev, 0x0043,
					(b43legacy_radio_read16(dev, 0x0043)
					 & 0xFFF0) | 0x0009);
		loop1_cnt = 9;
	} else if (phy->radio_rev == 8) {
		b43legacy_radio_write16(dev, 0x0043, 0x000F);
		loop1_cnt = 15;
	} else
		loop1_cnt = 0;

	b43legacy_phy_set_baseband_attenuation(dev, 11);

	if (phy->rev >= 3)
		b43legacy_phy_write(dev, 0x080F, 0xC020);
	else
		b43legacy_phy_write(dev, 0x080F, 0x8020);
	b43legacy_phy_write(dev, 0x0810, 0x0000);

	b43legacy_phy_write(dev, 0x002B,
			    (b43legacy_phy_read(dev, 0x002B)
			     & 0xFFC0) | 0x0001);
	b43legacy_phy_write(dev, 0x002B,
			    (b43legacy_phy_read(dev, 0x002B)
			     & 0xC0FF) | 0x0800);
	b43legacy_phy_write(dev, 0x0811,
			    b43legacy_phy_read(dev, 0x0811) | 0x0100);
	b43legacy_phy_write(dev, 0x0812,
			    b43legacy_phy_read(dev, 0x0812) & 0xCFFF);
	if (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_EXTLNA) {
		if (phy->rev >= 7) {
			b43legacy_phy_write(dev, 0x0811,
					    b43legacy_phy_read(dev, 0x0811)
					    | 0x0800);
			b43legacy_phy_write(dev, 0x0812,
					    b43legacy_phy_read(dev, 0x0812)
					    | 0x8000);
		}
	}
	b43legacy_radio_write16(dev, 0x007A,
				b43legacy_radio_read16(dev, 0x007A)
				& 0x00F7);

	for (i = 0; i < loop1_cnt; i++) {
		b43legacy_radio_write16(dev, 0x0043, loop1_cnt);
		b43legacy_phy_write(dev, 0x0812,
				    (b43legacy_phy_read(dev, 0x0812)
				     & 0xF0FF) | (i << 8));
		b43legacy_phy_write(dev, 0x0015,
				    (b43legacy_phy_read(dev, 0x0015)
				     & 0x0FFF) | 0xA000);
		b43legacy_phy_write(dev, 0x0015,
				    (b43legacy_phy_read(dev, 0x0015)
				     & 0x0FFF) | 0xF000);
		udelay(20);
		if (b43legacy_phy_read(dev, 0x002D) >= 0x0DFC)
			break;
	}
	loop1_done = i;
	loop1_omitted = loop1_cnt - loop1_done;

	loop2_done = 0;
	if (loop1_done >= 8) {
		b43legacy_phy_write(dev, 0x0812,
				    b43legacy_phy_read(dev, 0x0812)
				    | 0x0030);
		for (i = loop1_done - 8; i < 16; i++) {
			b43legacy_phy_write(dev, 0x0812,
					    (b43legacy_phy_read(dev, 0x0812)
					     & 0xF0FF) | (i << 8));
			b43legacy_phy_write(dev, 0x0015,
					    (b43legacy_phy_read(dev, 0x0015)
					     & 0x0FFF) | 0xA000);
			b43legacy_phy_write(dev, 0x0015,
					    (b43legacy_phy_read(dev, 0x0015)
					     & 0x0FFF) | 0xF000);
			udelay(20);
			if (b43legacy_phy_read(dev, 0x002D) >= 0x0DFC)
				break;
		}
	}

	if (phy->rev != 1) {
		b43legacy_phy_write(dev, 0x0814, backup_phy[4]);
		b43legacy_phy_write(dev, 0x0815, backup_phy[5]);
	}
	b43legacy_phy_write(dev, 0x005A, backup_phy[6]);
	b43legacy_phy_write(dev, 0x0059, backup_phy[7]);
	b43legacy_phy_write(dev, 0x0058, backup_phy[8]);
	b43legacy_phy_write(dev, 0x000A, backup_phy[9]);
	b43legacy_phy_write(dev, 0x0003, backup_phy[10]);
	b43legacy_phy_write(dev, 0x080F, backup_phy[11]);
	b43legacy_phy_write(dev, 0x0810, backup_phy[12]);
	b43legacy_phy_write(dev, 0x002B, backup_phy[13]);
	b43legacy_phy_write(dev, 0x0015, backup_phy[14]);

	b43legacy_phy_set_baseband_attenuation(dev, backup_bband);

	b43legacy_radio_write16(dev, 0x0052, backup_radio[0]);
	b43legacy_radio_write16(dev, 0x0043, backup_radio[1]);
	b43legacy_radio_write16(dev, 0x007A, backup_radio[2]);

	b43legacy_phy_write(dev, 0x0811, backup_phy[2] | 0x0003);
	udelay(10);
	b43legacy_phy_write(dev, 0x0811, backup_phy[2]);
	b43legacy_phy_write(dev, 0x0812, backup_phy[3]);
	b43legacy_phy_write(dev, 0x0429, backup_phy[0]);
	b43legacy_phy_write(dev, 0x0001, backup_phy[1]);

	phy->loopback_gain[0] = ((loop1_done * 6) - (loop1_omitted * 4)) - 11;
	phy->loopback_gain[1] = (24 - (3 * loop2_done)) * 2;
}