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
typedef  int u32 ;
struct fast_ant_train {int /*<<< orphan*/  FAT_State; scalar_t__ TrainIdx; scalar_t__* antAveRSSI; scalar_t__* antRSSIcnt; scalar_t__* antSumRSSI; scalar_t__* Bssid; } ;
struct odm_dm_struct {int* mp_mode; int /*<<< orphan*/  bIsMPChip; struct fast_ant_train DM_FatTable; struct adapter* Adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  FAT_NORMAL_STATE ; 
 int bMaskByte0 ; 
 int bMaskByte1 ; 
 int bMaskDWord ; 
 int phy_query_bb_reg (struct adapter*,int,int) ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int,int,int) ; 

__attribute__((used)) static void dm_fast_training_init(struct odm_dm_struct *dm_odm)
{
	struct adapter *adapter = dm_odm->Adapter;
	u32 value32, i;
	struct fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;

	if (*dm_odm->mp_mode == 1)
		return;

	for (i = 0; i < 6; i++) {
		dm_fat_tbl->Bssid[i] = 0;
		dm_fat_tbl->antSumRSSI[i] = 0;
		dm_fat_tbl->antRSSIcnt[i] = 0;
		dm_fat_tbl->antAveRSSI[i] = 0;
	}
	dm_fat_tbl->TrainIdx = 0;
	dm_fat_tbl->FAT_State = FAT_NORMAL_STATE;

	/* MAC Setting */
	value32 = phy_query_bb_reg(adapter, 0x4c, bMaskDWord);
	phy_set_bb_reg(adapter, 0x4c, bMaskDWord,
		       value32 | (BIT(23) | BIT(25)));
	value32 = phy_query_bb_reg(adapter,  0x7B4, bMaskDWord);
	phy_set_bb_reg(adapter, 0x7b4, bMaskDWord,
		       value32 | (BIT(16) | BIT(17)));

	/* Match MAC ADDR */
	phy_set_bb_reg(adapter, 0x7b4, 0xFFFF, 0);
	phy_set_bb_reg(adapter, 0x7b0, bMaskDWord, 0);

	phy_set_bb_reg(adapter, 0x870, BIT(9) | BIT(8), 0);
	phy_set_bb_reg(adapter, 0x864, BIT(10), 0);
	phy_set_bb_reg(adapter, 0xb2c, BIT(22), 0);
	phy_set_bb_reg(adapter, 0xb2c, BIT(31), 1);
	phy_set_bb_reg(adapter, 0xca4, bMaskDWord, 0x000000a0);

	/* antenna mapping table */
	if (!dm_odm->bIsMPChip) { /* testchip */
		phy_set_bb_reg(adapter, 0x858, BIT(10) | BIT(9) | BIT(8), 1);
		phy_set_bb_reg(adapter, 0x858, BIT(13) | BIT(12) | BIT(11), 2);
	} else { /* MPchip */
		phy_set_bb_reg(adapter, 0x914, bMaskByte0, 1);
		phy_set_bb_reg(adapter, 0x914, bMaskByte1, 2);
	}

	/* Default Ant Setting when no fast training */
	phy_set_bb_reg(adapter, 0x80c, BIT(21), 1);
	phy_set_bb_reg(adapter, 0x864, BIT(5) | BIT(4) | BIT(3), 0);
	phy_set_bb_reg(adapter, 0x864, BIT(8) | BIT(7) | BIT(6), 1);

	/* Enter Traing state */
	phy_set_bb_reg(adapter, 0x864, BIT(2) | BIT(1) | BIT(0), 1);
	phy_set_bb_reg(adapter, 0xc50, BIT(7), 1);
}