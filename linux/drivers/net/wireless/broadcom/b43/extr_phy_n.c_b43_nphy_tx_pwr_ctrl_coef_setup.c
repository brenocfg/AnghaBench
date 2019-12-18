#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_n {scalar_t__ hang_avoid; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_TABLE_ADDR ; 
 int /*<<< orphan*/  B43_NPHY_TABLE_DATAHI ; 
 int /*<<< orphan*/  B43_NPHY_TABLE_DATALO ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_SHM_SH_NPHY_TXPWR_INDX0 ; 
 int /*<<< orphan*/  B43_SHM_SH_NPHY_TXPWR_INDX1 ; 
 int /*<<< orphan*/  b43_nphy_stay_in_carrier_search (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_ntab_read_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* loscale ; 

__attribute__((used)) static void b43_nphy_tx_pwr_ctrl_coef_setup(struct b43_wldev *dev)
{
	struct b43_phy_n *nphy = dev->phy.n;
	int i, j;
	u32 tmp;
	u32 cur_real, cur_imag, real_part, imag_part;

	u16 buffer[7];

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, true);

	b43_ntab_read_bulk(dev, B43_NTAB16(15, 80), 7, buffer);

	for (i = 0; i < 2; i++) {
		tmp = ((buffer[i * 2] & 0x3FF) << 10) |
			(buffer[i * 2 + 1] & 0x3FF);
		b43_phy_write(dev, B43_NPHY_TABLE_ADDR,
				(((i + 26) << 10) | 320));
		for (j = 0; j < 128; j++) {
			b43_phy_write(dev, B43_NPHY_TABLE_DATAHI,
					((tmp >> 16) & 0xFFFF));
			b43_phy_write(dev, B43_NPHY_TABLE_DATALO,
					(tmp & 0xFFFF));
		}
	}

	for (i = 0; i < 2; i++) {
		tmp = buffer[5 + i];
		real_part = (tmp >> 8) & 0xFF;
		imag_part = (tmp & 0xFF);
		b43_phy_write(dev, B43_NPHY_TABLE_ADDR,
				(((i + 26) << 10) | 448));

		if (dev->phy.rev >= 3) {
			cur_real = real_part;
			cur_imag = imag_part;
			tmp = ((cur_real & 0xFF) << 8) | (cur_imag & 0xFF);
		}

		for (j = 0; j < 128; j++) {
			if (dev->phy.rev < 3) {
				cur_real = (real_part * loscale[j] + 128) >> 8;
				cur_imag = (imag_part * loscale[j] + 128) >> 8;
				tmp = ((cur_real & 0xFF) << 8) |
					(cur_imag & 0xFF);
			}
			b43_phy_write(dev, B43_NPHY_TABLE_DATAHI,
					((tmp >> 16) & 0xFFFF));
			b43_phy_write(dev, B43_NPHY_TABLE_DATALO,
					(tmp & 0xFFFF));
		}
	}

	if (dev->phy.rev >= 3) {
		b43_shm_write16(dev, B43_SHM_SHARED,
				B43_SHM_SH_NPHY_TXPWR_INDX0, 0xFFFF);
		b43_shm_write16(dev, B43_SHM_SHARED,
				B43_SHM_SH_NPHY_TXPWR_INDX1, 0xFFFF);
	}

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, false);
}