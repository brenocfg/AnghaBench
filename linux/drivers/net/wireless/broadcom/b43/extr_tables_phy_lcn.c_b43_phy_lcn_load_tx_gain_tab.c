#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int u16 ;
struct b43_wldev {TYPE_2__* dev; } ;
struct b43_lcntab_tx_gain_tbl_entry {int pad; int pga; int gm; int dac; int bb_mult; } ;
struct TYPE_4__ {TYPE_1__* bus_sprom; } ;
struct TYPE_3__ {int boardflags_lo; } ;

/* Variables and functions */
 int B43_BFL_FEM ; 
 int /*<<< orphan*/  B43_LCNTAB32 (int,int) ; 
 size_t B43_LCNTAB_TX_GAIN_SIZE ; 
 size_t b43_lcntab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_lcntab_write (struct b43_wldev*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void b43_phy_lcn_load_tx_gain_tab(struct b43_wldev *dev,
			const struct b43_lcntab_tx_gain_tbl_entry *gain_table)
{
	u32 i;
	u32 val;

	u16 pa_gain = 0x70;
	if (dev->dev->bus_sprom->boardflags_lo & B43_BFL_FEM)
		pa_gain = 0x10;

	for (i = 0; i < B43_LCNTAB_TX_GAIN_SIZE; i++) {
		val = ((pa_gain << 24) |
		       (gain_table[i].pad << 16) |
		       (gain_table[i].pga << 8) |
			gain_table[i].gm);
		b43_lcntab_write(dev, B43_LCNTAB32(0x7, 0xc0 + i), val);

		/* brcmsmac doesn't maskset, we follow newer wl here */
		val = b43_lcntab_read(dev, B43_LCNTAB32(0x7, 0x140 + i));
		val &= 0x000fffff;
		val |= ((gain_table[i].dac << 28) |
			(gain_table[i].bb_mult << 20));
		b43_lcntab_write(dev, B43_LCNTAB32(0x7, 0x140 + i), val);
	}
}