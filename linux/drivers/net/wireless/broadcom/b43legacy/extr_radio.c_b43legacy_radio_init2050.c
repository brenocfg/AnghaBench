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
typedef  int u32 ;
typedef  int u16 ;
struct b43legacy_phy {scalar_t__ type; int rev; int analog; int radio_rev; scalar_t__ gmode; int /*<<< orphan*/  channel; } ;
struct b43legacy_wldev {TYPE_3__* dev; struct b43legacy_phy phy; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {int boardflags_lo; } ;
struct TYPE_5__ {TYPE_1__ sprom; } ;

/* Variables and functions */
 int B43legacy_BFL_EXTLNA ; 
 int B43legacy_MMIO_CHANNEL_EXT ; 
 int B43legacy_MMIO_PHY_RADIO ; 
 scalar_t__ B43legacy_PHYTYPE_B ; 
 int B43legacy_PHY_G_CRS ; 
 int /*<<< orphan*/  LPD (int,int,int) ; 
 int b43legacy_get_812_value (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_calibrationvalue (struct b43legacy_wldev*) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_selectchannel (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int flip_4bit (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

u16 b43legacy_radio_init2050(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 backup[21] = { 0 };
	u16 ret;
	u16 i;
	u16 j;
	u32 tmp1 = 0;
	u32 tmp2 = 0;

	backup[0] = b43legacy_radio_read16(dev, 0x0043);
	backup[14] = b43legacy_radio_read16(dev, 0x0051);
	backup[15] = b43legacy_radio_read16(dev, 0x0052);
	backup[1] = b43legacy_phy_read(dev, 0x0015);
	backup[16] = b43legacy_phy_read(dev, 0x005A);
	backup[17] = b43legacy_phy_read(dev, 0x0059);
	backup[18] = b43legacy_phy_read(dev, 0x0058);
	if (phy->type == B43legacy_PHYTYPE_B) {
		backup[2] = b43legacy_phy_read(dev, 0x0030);
		backup[3] = b43legacy_read16(dev, 0x03EC);
		b43legacy_phy_write(dev, 0x0030, 0x00FF);
		b43legacy_write16(dev, 0x03EC, 0x3F3F);
	} else {
		if (phy->gmode) {
			backup[4] = b43legacy_phy_read(dev, 0x0811);
			backup[5] = b43legacy_phy_read(dev, 0x0812);
			backup[6] = b43legacy_phy_read(dev, 0x0814);
			backup[7] = b43legacy_phy_read(dev, 0x0815);
			backup[8] = b43legacy_phy_read(dev,
						       B43legacy_PHY_G_CRS);
			backup[9] = b43legacy_phy_read(dev, 0x0802);
			b43legacy_phy_write(dev, 0x0814,
					    (b43legacy_phy_read(dev, 0x0814)
					    | 0x0003));
			b43legacy_phy_write(dev, 0x0815,
					    (b43legacy_phy_read(dev, 0x0815)
					    & 0xFFFC));
			b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
					    (b43legacy_phy_read(dev,
					    B43legacy_PHY_G_CRS) & 0x7FFF));
			b43legacy_phy_write(dev, 0x0802,
					    (b43legacy_phy_read(dev, 0x0802)
					    & 0xFFFC));
			if (phy->rev > 1) { /* loopback gain enabled */
				backup[19] = b43legacy_phy_read(dev, 0x080F);
				backup[20] = b43legacy_phy_read(dev, 0x0810);
				if (phy->rev >= 3)
					b43legacy_phy_write(dev, 0x080F,
							    0xC020);
				else
					b43legacy_phy_write(dev, 0x080F,
							    0x8020);
				b43legacy_phy_write(dev, 0x0810, 0x0000);
			}
			b43legacy_phy_write(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(0, 1, 1)));
			if (phy->rev < 7 ||
			    !(dev->dev->bus->sprom.boardflags_lo
			    & B43legacy_BFL_EXTLNA))
				b43legacy_phy_write(dev, 0x0811, 0x01B3);
			else
				b43legacy_phy_write(dev, 0x0811, 0x09B3);
		}
	}
	b43legacy_write16(dev, B43legacy_MMIO_PHY_RADIO,
			(b43legacy_read16(dev, B43legacy_MMIO_PHY_RADIO)
					  | 0x8000));
	backup[10] = b43legacy_phy_read(dev, 0x0035);
	b43legacy_phy_write(dev, 0x0035,
			    (b43legacy_phy_read(dev, 0x0035) & 0xFF7F));
	backup[11] = b43legacy_read16(dev, 0x03E6);
	backup[12] = b43legacy_read16(dev, B43legacy_MMIO_CHANNEL_EXT);

	/* Initialization */
	if (phy->analog == 0)
		b43legacy_write16(dev, 0x03E6, 0x0122);
	else {
		if (phy->analog >= 2)
			b43legacy_phy_write(dev, 0x0003,
					    (b43legacy_phy_read(dev, 0x0003)
					    & 0xFFBF) | 0x0040);
		b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT,
				  (b43legacy_read16(dev,
				  B43legacy_MMIO_CHANNEL_EXT) | 0x2000));
	}

	ret = b43legacy_radio_calibrationvalue(dev);

	if (phy->type == B43legacy_PHYTYPE_B)
		b43legacy_radio_write16(dev, 0x0078, 0x0026);

	if (phy->gmode)
		b43legacy_phy_write(dev, 0x0812,
				    b43legacy_get_812_value(dev,
				    LPD(0, 1, 1)));
	b43legacy_phy_write(dev, 0x0015, 0xBFAF);
	b43legacy_phy_write(dev, 0x002B, 0x1403);
	if (phy->gmode)
		b43legacy_phy_write(dev, 0x0812,
				    b43legacy_get_812_value(dev,
				    LPD(0, 0, 1)));
	b43legacy_phy_write(dev, 0x0015, 0xBFA0);
	b43legacy_radio_write16(dev, 0x0051,
				(b43legacy_radio_read16(dev, 0x0051)
				| 0x0004));
	if (phy->radio_rev == 8)
		b43legacy_radio_write16(dev, 0x0043, 0x001F);
	else {
		b43legacy_radio_write16(dev, 0x0052, 0x0000);
		b43legacy_radio_write16(dev, 0x0043,
					(b43legacy_radio_read16(dev, 0x0043)
					& 0xFFF0) | 0x0009);
	}
	b43legacy_phy_write(dev, 0x0058, 0x0000);

	for (i = 0; i < 16; i++) {
		b43legacy_phy_write(dev, 0x005A, 0x0480);
		b43legacy_phy_write(dev, 0x0059, 0xC810);
		b43legacy_phy_write(dev, 0x0058, 0x000D);
		if (phy->gmode)
			b43legacy_phy_write(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(1, 0, 1)));
		b43legacy_phy_write(dev, 0x0015, 0xAFB0);
		udelay(10);
		if (phy->gmode)
			b43legacy_phy_write(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(1, 0, 1)));
		b43legacy_phy_write(dev, 0x0015, 0xEFB0);
		udelay(10);
		if (phy->gmode)
			b43legacy_phy_write(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(1, 0, 0)));
		b43legacy_phy_write(dev, 0x0015, 0xFFF0);
		udelay(20);
		tmp1 += b43legacy_phy_read(dev, 0x002D);
		b43legacy_phy_write(dev, 0x0058, 0x0000);
		if (phy->gmode)
			b43legacy_phy_write(dev, 0x0812,
					    b43legacy_get_812_value(dev,
					    LPD(1, 0, 1)));
		b43legacy_phy_write(dev, 0x0015, 0xAFB0);
	}

	tmp1++;
	tmp1 >>= 9;
	udelay(10);
	b43legacy_phy_write(dev, 0x0058, 0x0000);

	for (i = 0; i < 16; i++) {
		b43legacy_radio_write16(dev, 0x0078, (flip_4bit(i) << 1)
					| 0x0020);
		backup[13] = b43legacy_radio_read16(dev, 0x0078);
		udelay(10);
		for (j = 0; j < 16; j++) {
			b43legacy_phy_write(dev, 0x005A, 0x0D80);
			b43legacy_phy_write(dev, 0x0059, 0xC810);
			b43legacy_phy_write(dev, 0x0058, 0x000D);
			if (phy->gmode)
				b43legacy_phy_write(dev, 0x0812,
						    b43legacy_get_812_value(dev,
						    LPD(1, 0, 1)));
			b43legacy_phy_write(dev, 0x0015, 0xAFB0);
			udelay(10);
			if (phy->gmode)
				b43legacy_phy_write(dev, 0x0812,
						    b43legacy_get_812_value(dev,
						    LPD(1, 0, 1)));
			b43legacy_phy_write(dev, 0x0015, 0xEFB0);
			udelay(10);
			if (phy->gmode)
				b43legacy_phy_write(dev, 0x0812,
						    b43legacy_get_812_value(dev,
						    LPD(1, 0, 0)));
			b43legacy_phy_write(dev, 0x0015, 0xFFF0);
			udelay(10);
			tmp2 += b43legacy_phy_read(dev, 0x002D);
			b43legacy_phy_write(dev, 0x0058, 0x0000);
			if (phy->gmode)
				b43legacy_phy_write(dev, 0x0812,
						    b43legacy_get_812_value(dev,
						    LPD(1, 0, 1)));
			b43legacy_phy_write(dev, 0x0015, 0xAFB0);
		}
		tmp2++;
		tmp2 >>= 8;
		if (tmp1 < tmp2)
			break;
	}

	/* Restore the registers */
	b43legacy_phy_write(dev, 0x0015, backup[1]);
	b43legacy_radio_write16(dev, 0x0051, backup[14]);
	b43legacy_radio_write16(dev, 0x0052, backup[15]);
	b43legacy_radio_write16(dev, 0x0043, backup[0]);
	b43legacy_phy_write(dev, 0x005A, backup[16]);
	b43legacy_phy_write(dev, 0x0059, backup[17]);
	b43legacy_phy_write(dev, 0x0058, backup[18]);
	b43legacy_write16(dev, 0x03E6, backup[11]);
	if (phy->analog != 0)
		b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT, backup[12]);
	b43legacy_phy_write(dev, 0x0035, backup[10]);
	b43legacy_radio_selectchannel(dev, phy->channel, 1);
	if (phy->type == B43legacy_PHYTYPE_B) {
		b43legacy_phy_write(dev, 0x0030, backup[2]);
		b43legacy_write16(dev, 0x03EC, backup[3]);
	} else {
		if (phy->gmode) {
			b43legacy_write16(dev, B43legacy_MMIO_PHY_RADIO,
					  (b43legacy_read16(dev,
					  B43legacy_MMIO_PHY_RADIO) & 0x7FFF));
			b43legacy_phy_write(dev, 0x0811, backup[4]);
			b43legacy_phy_write(dev, 0x0812, backup[5]);
			b43legacy_phy_write(dev, 0x0814, backup[6]);
			b43legacy_phy_write(dev, 0x0815, backup[7]);
			b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
					    backup[8]);
			b43legacy_phy_write(dev, 0x0802, backup[9]);
			if (phy->rev > 1) {
				b43legacy_phy_write(dev, 0x080F, backup[19]);
				b43legacy_phy_write(dev, 0x0810, backup[20]);
			}
		}
	}
	if (i >= 15)
		ret = backup[13];

	return ret;
}