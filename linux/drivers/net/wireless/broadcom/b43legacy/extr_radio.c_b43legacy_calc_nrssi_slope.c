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
struct b43legacy_phy {int type; int rev; int analog; int nrssislope; int* nrssi; int radio_rev; int /*<<< orphan*/  channel; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 int B43legacy_MMIO_CHANNEL_EXT ; 
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 int B43legacy_PHY_G_CRS ; 
 int B43legacy_PHY_G_LO_CONTROL ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_offset (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_calc_nrssi_threshold (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_nrssi_mem_update (struct b43legacy_wldev*) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_set_all_gains (struct b43legacy_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43legacy_set_original_gains (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_synth_pu_workaround (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void b43legacy_calc_nrssi_slope(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 backup[18] = { 0 };
	u16 tmp;
	s16 nrssi0;
	s16 nrssi1;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
		backup[0] = b43legacy_radio_read16(dev, 0x007A);
		backup[1] = b43legacy_radio_read16(dev, 0x0052);
		backup[2] = b43legacy_radio_read16(dev, 0x0043);
		backup[3] = b43legacy_phy_read(dev, 0x0030);
		backup[4] = b43legacy_phy_read(dev, 0x0026);
		backup[5] = b43legacy_phy_read(dev, 0x0015);
		backup[6] = b43legacy_phy_read(dev, 0x002A);
		backup[7] = b43legacy_phy_read(dev, 0x0020);
		backup[8] = b43legacy_phy_read(dev, 0x005A);
		backup[9] = b43legacy_phy_read(dev, 0x0059);
		backup[10] = b43legacy_phy_read(dev, 0x0058);
		backup[11] = b43legacy_read16(dev, 0x03E2);
		backup[12] = b43legacy_read16(dev, 0x03E6);
		backup[13] = b43legacy_read16(dev, B43legacy_MMIO_CHANNEL_EXT);

		tmp  = b43legacy_radio_read16(dev, 0x007A);
		tmp &= (phy->rev >= 5) ? 0x007F : 0x000F;
		b43legacy_radio_write16(dev, 0x007A, tmp);
		b43legacy_phy_write(dev, 0x0030, 0x00FF);
		b43legacy_write16(dev, 0x03EC, 0x7F7F);
		b43legacy_phy_write(dev, 0x0026, 0x0000);
		b43legacy_phy_write(dev, 0x0015,
				    b43legacy_phy_read(dev, 0x0015) | 0x0020);
		b43legacy_phy_write(dev, 0x002A, 0x08A3);
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					| 0x0080);

		nrssi0 = (s16)b43legacy_phy_read(dev, 0x0027);
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					& 0x007F);
		if (phy->analog >= 2)
			b43legacy_write16(dev, 0x03E6, 0x0040);
		else if (phy->analog == 0)
			b43legacy_write16(dev, 0x03E6, 0x0122);
		else
			b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT,
					  b43legacy_read16(dev,
					  B43legacy_MMIO_CHANNEL_EXT) & 0x2000);
		b43legacy_phy_write(dev, 0x0020, 0x3F3F);
		b43legacy_phy_write(dev, 0x0015, 0xF330);
		b43legacy_radio_write16(dev, 0x005A, 0x0060);
		b43legacy_radio_write16(dev, 0x0043,
					b43legacy_radio_read16(dev, 0x0043)
					& 0x00F0);
		b43legacy_phy_write(dev, 0x005A, 0x0480);
		b43legacy_phy_write(dev, 0x0059, 0x0810);
		b43legacy_phy_write(dev, 0x0058, 0x000D);
		udelay(20);

		nrssi1 = (s16)b43legacy_phy_read(dev, 0x0027);
		b43legacy_phy_write(dev, 0x0030, backup[3]);
		b43legacy_radio_write16(dev, 0x007A, backup[0]);
		b43legacy_write16(dev, 0x03E2, backup[11]);
		b43legacy_phy_write(dev, 0x0026, backup[4]);
		b43legacy_phy_write(dev, 0x0015, backup[5]);
		b43legacy_phy_write(dev, 0x002A, backup[6]);
		b43legacy_synth_pu_workaround(dev, phy->channel);
		if (phy->analog != 0)
			b43legacy_write16(dev, 0x03F4, backup[13]);

		b43legacy_phy_write(dev, 0x0020, backup[7]);
		b43legacy_phy_write(dev, 0x005A, backup[8]);
		b43legacy_phy_write(dev, 0x0059, backup[9]);
		b43legacy_phy_write(dev, 0x0058, backup[10]);
		b43legacy_radio_write16(dev, 0x0052, backup[1]);
		b43legacy_radio_write16(dev, 0x0043, backup[2]);

		if (nrssi0 == nrssi1)
			phy->nrssislope = 0x00010000;
		else
			phy->nrssislope = 0x00400000 / (nrssi0 - nrssi1);

		if (nrssi0 <= -4) {
			phy->nrssi[0] = nrssi0;
			phy->nrssi[1] = nrssi1;
		}
		break;
	case B43legacy_PHYTYPE_G:
		if (phy->radio_rev >= 9)
			return;
		if (phy->radio_rev == 8)
			b43legacy_calc_nrssi_offset(dev);

		b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
				    b43legacy_phy_read(dev, B43legacy_PHY_G_CRS)
				    & 0x7FFF);
		b43legacy_phy_write(dev, 0x0802,
				    b43legacy_phy_read(dev, 0x0802) & 0xFFFC);
		backup[7] = b43legacy_read16(dev, 0x03E2);
		b43legacy_write16(dev, 0x03E2,
				  b43legacy_read16(dev, 0x03E2) | 0x8000);
		backup[0] = b43legacy_radio_read16(dev, 0x007A);
		backup[1] = b43legacy_radio_read16(dev, 0x0052);
		backup[2] = b43legacy_radio_read16(dev, 0x0043);
		backup[3] = b43legacy_phy_read(dev, 0x0015);
		backup[4] = b43legacy_phy_read(dev, 0x005A);
		backup[5] = b43legacy_phy_read(dev, 0x0059);
		backup[6] = b43legacy_phy_read(dev, 0x0058);
		backup[8] = b43legacy_read16(dev, 0x03E6);
		backup[9] = b43legacy_read16(dev, B43legacy_MMIO_CHANNEL_EXT);
		if (phy->rev >= 3) {
			backup[10] = b43legacy_phy_read(dev, 0x002E);
			backup[11] = b43legacy_phy_read(dev, 0x002F);
			backup[12] = b43legacy_phy_read(dev, 0x080F);
			backup[13] = b43legacy_phy_read(dev,
						B43legacy_PHY_G_LO_CONTROL);
			backup[14] = b43legacy_phy_read(dev, 0x0801);
			backup[15] = b43legacy_phy_read(dev, 0x0060);
			backup[16] = b43legacy_phy_read(dev, 0x0014);
			backup[17] = b43legacy_phy_read(dev, 0x0478);
			b43legacy_phy_write(dev, 0x002E, 0);
			b43legacy_phy_write(dev, B43legacy_PHY_G_LO_CONTROL, 0);
			switch (phy->rev) {
			case 4: case 6: case 7:
				b43legacy_phy_write(dev, 0x0478,
						    b43legacy_phy_read(dev,
						    0x0478) | 0x0100);
				b43legacy_phy_write(dev, 0x0801,
						    b43legacy_phy_read(dev,
						    0x0801) | 0x0040);
				break;
			case 3: case 5:
				b43legacy_phy_write(dev, 0x0801,
						    b43legacy_phy_read(dev,
						    0x0801) & 0xFFBF);
				break;
			}
			b43legacy_phy_write(dev, 0x0060,
					    b43legacy_phy_read(dev, 0x0060)
					    | 0x0040);
			b43legacy_phy_write(dev, 0x0014,
					    b43legacy_phy_read(dev, 0x0014)
					    | 0x0200);
		}
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					| 0x0070);
		b43legacy_set_all_gains(dev, 0, 8, 0);
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					& 0x00F7);
		if (phy->rev >= 2) {
			b43legacy_phy_write(dev, 0x0811,
					    (b43legacy_phy_read(dev, 0x0811)
					    & 0xFFCF) | 0x0030);
			b43legacy_phy_write(dev, 0x0812,
					    (b43legacy_phy_read(dev, 0x0812)
					    & 0xFFCF) | 0x0010);
		}
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					| 0x0080);
		udelay(20);

		nrssi0 = (s16)((b43legacy_phy_read(dev, 0x047F) >> 8) & 0x003F);
		if (nrssi0 >= 0x0020)
			nrssi0 -= 0x0040;

		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					& 0x007F);
		if (phy->analog >= 2)
			b43legacy_phy_write(dev, 0x0003,
					    (b43legacy_phy_read(dev, 0x0003)
					    & 0xFF9F) | 0x0040);

		b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT,
				  b43legacy_read16(dev,
				  B43legacy_MMIO_CHANNEL_EXT) | 0x2000);
		b43legacy_radio_write16(dev, 0x007A,
					b43legacy_radio_read16(dev, 0x007A)
					| 0x000F);
		b43legacy_phy_write(dev, 0x0015, 0xF330);
		if (phy->rev >= 2) {
			b43legacy_phy_write(dev, 0x0812,
					    (b43legacy_phy_read(dev, 0x0812)
					    & 0xFFCF) | 0x0020);
			b43legacy_phy_write(dev, 0x0811,
					    (b43legacy_phy_read(dev, 0x0811)
					    & 0xFFCF) | 0x0020);
		}

		b43legacy_set_all_gains(dev, 3, 0, 1);
		if (phy->radio_rev == 8)
			b43legacy_radio_write16(dev, 0x0043, 0x001F);
		else {
			tmp = b43legacy_radio_read16(dev, 0x0052) & 0xFF0F;
			b43legacy_radio_write16(dev, 0x0052, tmp | 0x0060);
			tmp = b43legacy_radio_read16(dev, 0x0043) & 0xFFF0;
			b43legacy_radio_write16(dev, 0x0043, tmp | 0x0009);
		}
		b43legacy_phy_write(dev, 0x005A, 0x0480);
		b43legacy_phy_write(dev, 0x0059, 0x0810);
		b43legacy_phy_write(dev, 0x0058, 0x000D);
		udelay(20);
		nrssi1 = (s16)((b43legacy_phy_read(dev, 0x047F) >> 8) & 0x003F);
		if (nrssi1 >= 0x0020)
			nrssi1 -= 0x0040;
		if (nrssi0 == nrssi1)
			phy->nrssislope = 0x00010000;
		else
			phy->nrssislope = 0x00400000 / (nrssi0 - nrssi1);
		if (nrssi0 >= -4) {
			phy->nrssi[0] = nrssi1;
			phy->nrssi[1] = nrssi0;
		}
		if (phy->rev >= 3) {
			b43legacy_phy_write(dev, 0x002E, backup[10]);
			b43legacy_phy_write(dev, 0x002F, backup[11]);
			b43legacy_phy_write(dev, 0x080F, backup[12]);
			b43legacy_phy_write(dev, B43legacy_PHY_G_LO_CONTROL,
					    backup[13]);
		}
		if (phy->rev >= 2) {
			b43legacy_phy_write(dev, 0x0812,
					    b43legacy_phy_read(dev, 0x0812)
					    & 0xFFCF);
			b43legacy_phy_write(dev, 0x0811,
					    b43legacy_phy_read(dev, 0x0811)
					    & 0xFFCF);
		}

		b43legacy_radio_write16(dev, 0x007A, backup[0]);
		b43legacy_radio_write16(dev, 0x0052, backup[1]);
		b43legacy_radio_write16(dev, 0x0043, backup[2]);
		b43legacy_write16(dev, 0x03E2, backup[7]);
		b43legacy_write16(dev, 0x03E6, backup[8]);
		b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT, backup[9]);
		b43legacy_phy_write(dev, 0x0015, backup[3]);
		b43legacy_phy_write(dev, 0x005A, backup[4]);
		b43legacy_phy_write(dev, 0x0059, backup[5]);
		b43legacy_phy_write(dev, 0x0058, backup[6]);
		b43legacy_synth_pu_workaround(dev, phy->channel);
		b43legacy_phy_write(dev, 0x0802,
				    b43legacy_phy_read(dev, 0x0802) | 0x0003);
		b43legacy_set_original_gains(dev);
		b43legacy_phy_write(dev, B43legacy_PHY_G_CRS,
				    b43legacy_phy_read(dev, B43legacy_PHY_G_CRS)
				    | 0x8000);
		if (phy->rev >= 3) {
			b43legacy_phy_write(dev, 0x0801, backup[14]);
			b43legacy_phy_write(dev, 0x0060, backup[15]);
			b43legacy_phy_write(dev, 0x0014, backup[16]);
			b43legacy_phy_write(dev, 0x0478, backup[17]);
		}
		b43legacy_nrssi_mem_update(dev);
		b43legacy_calc_nrssi_threshold(dev);
		break;
	default:
		B43legacy_BUG_ON(1);
	}
}