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
struct phytbl_info {int tbl_width; int tbl_len; int* tbl_ptr; scalar_t__ tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct lcnphy_tx_gain_tbl_entry {int gm; int pad; int pga; int dac; int bb_mult; } ;
struct brcms_phy {TYPE_1__* sh; } ;
struct TYPE_2__ {int boardflags; } ;

/* Variables and functions */
 int BFL_FEM ; 
 int /*<<< orphan*/  LCNPHY_TBL_ID_TXPWRCTL ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_GAIN_OFFSET ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_IQ_OFFSET ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static void
wlc_lcnphy_load_tx_gain_table(struct brcms_phy *pi,
			      const struct lcnphy_tx_gain_tbl_entry *gain_table)
{
	u32 j;
	struct phytbl_info tab;
	u32 val;
	u16 pa_gain;
	u16 gm_gain;

	if (pi->sh->boardflags & BFL_FEM)
		pa_gain = 0x10;
	else
		pa_gain = 0x60;
	tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
	tab.tbl_width = 32;
	tab.tbl_len = 1;
	tab.tbl_ptr = &val;

	/* fixed gm_gain value for iPA */
	gm_gain = 15;
	for (j = 0; j < 128; j++) {
		if (pi->sh->boardflags & BFL_FEM)
			gm_gain = gain_table[j].gm;
		val = (((u32) pa_gain << 24) |
		       (gain_table[j].pad << 16) |
		       (gain_table[j].pga << 8) | gm_gain);

		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_GAIN_OFFSET + j;
		wlc_lcnphy_write_table(pi, &tab);

		val = (gain_table[j].dac << 28) | (gain_table[j].bb_mult << 20);
		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_IQ_OFFSET + j;
		wlc_lcnphy_write_table(pi, &tab);
	}
}