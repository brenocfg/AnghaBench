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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct il_priv {TYPE_1__* cfg; } ;
struct il_eeprom_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * regulatory_bands; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/ * il_eeprom_band_1 ; 
 int /*<<< orphan*/ * il_eeprom_band_2 ; 
 int /*<<< orphan*/ * il_eeprom_band_3 ; 
 int /*<<< orphan*/ * il_eeprom_band_4 ; 
 int /*<<< orphan*/ * il_eeprom_band_5 ; 
 int /*<<< orphan*/ * il_eeprom_band_6 ; 
 int /*<<< orphan*/ * il_eeprom_band_7 ; 
 scalar_t__ il_eeprom_query_addr (struct il_priv const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il_init_band_reference(const struct il_priv *il, int eep_band,
		       int *eeprom_ch_count,
		       const struct il_eeprom_channel **eeprom_ch_info,
		       const u8 **eeprom_ch_idx)
{
	u32 offset = il->cfg->regulatory_bands[eep_band - 1];

	switch (eep_band) {
	case 1:		/* 2.4GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_1);
		*eeprom_ch_info =
		    (struct il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_1;
		break;
	case 2:		/* 4.9GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_2);
		*eeprom_ch_info =
		    (struct il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_2;
		break;
	case 3:		/* 5.2GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_3);
		*eeprom_ch_info =
		    (struct il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_3;
		break;
	case 4:		/* 5.5GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_4);
		*eeprom_ch_info =
		    (struct il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_4;
		break;
	case 5:		/* 5.7GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_5);
		*eeprom_ch_info =
		    (struct il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_5;
		break;
	case 6:		/* 2.4GHz ht40 channels */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_6);
		*eeprom_ch_info =
		    (struct il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_6;
		break;
	case 7:		/* 5 GHz ht40 channels */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_7);
		*eeprom_ch_info =
		    (struct il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_7;
		break;
	default:
		BUG();
	}
}