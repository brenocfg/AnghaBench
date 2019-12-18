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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct fast_ant_train {scalar_t__* antsel_c; scalar_t__* antsel_b; scalar_t__* antsel_a; } ;
struct odm_dm_struct {struct fast_ant_train DM_FatTable; } ;

/* Variables and functions */
 scalar_t__ AUX_ANT_CG_TRX ; 
 scalar_t__ BIT (int) ; 
 scalar_t__ MAIN_ANT ; 
 scalar_t__ MAIN_ANT_CG_TRX ; 

__attribute__((used)) static void update_tx_ant_88eu(struct odm_dm_struct *dm_odm, u8 ant, u32 mac_id)
{
	struct fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;
	u8 target_ant;

	if (ant == MAIN_ANT)
		target_ant = MAIN_ANT_CG_TRX;
	else
		target_ant = AUX_ANT_CG_TRX;
	dm_fat_tbl->antsel_a[mac_id] = target_ant & BIT(0);
	dm_fat_tbl->antsel_b[mac_id] = (target_ant & BIT(1)) >> 1;
	dm_fat_tbl->antsel_c[mac_id] = (target_ant & BIT(2)) >> 2;
}