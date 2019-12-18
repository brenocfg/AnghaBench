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
typedef  int u8 ;
typedef  size_t u32 ;
struct txpower_info {int** cck_index; int** ht40_1sindex; int** ht40_2sindexdiff; int** ht20indexdiff; int** ofdmindexdiff; int** ht40maxoffset; int** ht20maxoffset; int* tssi_a; int* tssi_b; } ;

/* Variables and functions */
 size_t CHANNEL_GROUP_MAX ; 
 size_t CHANNEL_GROUP_MAX_2G ; 
 size_t EEPROM_CCK_TX_PWR_INX_2G ; 
 void* EEPROM_DEFAULT_HT20_DIFF ; 
 void* EEPROM_DEFAULT_HT20_PWRMAXOFFSET ; 
 void* EEPROM_DEFAULT_HT40_2SDIFF ; 
 void* EEPROM_DEFAULT_HT40_PWRMAXOFFSET ; 
 void* EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF ; 
 void* EEPROM_DEFAULT_TSSI ; 
 int EEPROM_DEFAULT_TXPOWERLEVEL_2G ; 
 int EEPROM_DEFAULT_TXPOWERLEVEL_5G ; 
 size_t EEPROM_HT20_MAX_PWR_OFFSET_2G ; 
 size_t EEPROM_HT20_TX_PWR_INX_DIFF_2G ; 
 size_t EEPROM_HT40_1S_TX_PWR_INX_2G ; 
 int EEPROM_HT40_2S_TX_PWR_INX_DIFF_2G ; 
 size_t EEPROM_HT40_MAX_PWR_OFFSET_2G ; 
 size_t EEPROM_OFDM_TX_PWR_INX_DIFF_2G ; 
 size_t EEPROM_TSSI_AB_5G ; 
 size_t EEPROM_TSSI_A_5G ; 
 size_t EEPROM_TSSI_B_5G ; 
 size_t RF6052_MAX_PATH ; 
 int /*<<< orphan*/  memset (struct txpower_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92de_readpowervalue_fromprom(struct txpower_info *pwrinfo,
				 u8 *rom_content, bool autoloadfail)
{
	u32 rfpath, eeaddr, group, offset1, offset2;
	u8 i;

	memset(pwrinfo, 0, sizeof(struct txpower_info));
	if (autoloadfail) {
		for (group = 0; group < CHANNEL_GROUP_MAX; group++) {
			for (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) {
				if (group < CHANNEL_GROUP_MAX_2G) {
					pwrinfo->cck_index[rfpath][group] =
					    EEPROM_DEFAULT_TXPOWERLEVEL_2G;
					pwrinfo->ht40_1sindex[rfpath][group] =
					    EEPROM_DEFAULT_TXPOWERLEVEL_2G;
				} else {
					pwrinfo->ht40_1sindex[rfpath][group] =
					    EEPROM_DEFAULT_TXPOWERLEVEL_5G;
				}
				pwrinfo->ht40_2sindexdiff[rfpath][group] =
				    EEPROM_DEFAULT_HT40_2SDIFF;
				pwrinfo->ht20indexdiff[rfpath][group] =
				    EEPROM_DEFAULT_HT20_DIFF;
				pwrinfo->ofdmindexdiff[rfpath][group] =
				    EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF;
				pwrinfo->ht40maxoffset[rfpath][group] =
				    EEPROM_DEFAULT_HT40_PWRMAXOFFSET;
				pwrinfo->ht20maxoffset[rfpath][group] =
				    EEPROM_DEFAULT_HT20_PWRMAXOFFSET;
			}
		}
		for (i = 0; i < 3; i++) {
			pwrinfo->tssi_a[i] = EEPROM_DEFAULT_TSSI;
			pwrinfo->tssi_b[i] = EEPROM_DEFAULT_TSSI;
		}
		return;
	}

	/* Maybe autoload OK,buf the tx power index value is not filled.
	 * If we find it, we set it to default value. */
	for (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) {
		for (group = 0; group < CHANNEL_GROUP_MAX_2G; group++) {
			eeaddr = EEPROM_CCK_TX_PWR_INX_2G + (rfpath * 3)
				 + group;
			pwrinfo->cck_index[rfpath][group] =
					(rom_content[eeaddr] == 0xFF) ?
					     (eeaddr > 0x7B ?
					     EEPROM_DEFAULT_TXPOWERLEVEL_5G :
					     EEPROM_DEFAULT_TXPOWERLEVEL_2G) :
					     rom_content[eeaddr];
		}
	}
	for (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) {
		for (group = 0; group < CHANNEL_GROUP_MAX; group++) {
			offset1 = group / 3;
			offset2 = group % 3;
			eeaddr = EEPROM_HT40_1S_TX_PWR_INX_2G + (rfpath * 3) +
			    offset2 + offset1 * 21;
			pwrinfo->ht40_1sindex[rfpath][group] =
			    (rom_content[eeaddr] == 0xFF) ? (eeaddr > 0x7B ?
					     EEPROM_DEFAULT_TXPOWERLEVEL_5G :
					     EEPROM_DEFAULT_TXPOWERLEVEL_2G) :
						 rom_content[eeaddr];
		}
	}
	/* These just for 92D efuse offset. */
	for (group = 0; group < CHANNEL_GROUP_MAX; group++) {
		for (rfpath = 0; rfpath < RF6052_MAX_PATH; rfpath++) {
			int base1 = EEPROM_HT40_2S_TX_PWR_INX_DIFF_2G;

			offset1 = group / 3;
			offset2 = group % 3;

			if (rom_content[base1 + offset2 + offset1 * 21] != 0xFF)
				pwrinfo->ht40_2sindexdiff[rfpath][group] =
				    (rom_content[base1 +
				     offset2 + offset1 * 21] >> (rfpath * 4))
				     & 0xF;
			else
				pwrinfo->ht40_2sindexdiff[rfpath][group] =
				    EEPROM_DEFAULT_HT40_2SDIFF;
			if (rom_content[EEPROM_HT20_TX_PWR_INX_DIFF_2G + offset2
			    + offset1 * 21] != 0xFF)
				pwrinfo->ht20indexdiff[rfpath][group] =
				    (rom_content[EEPROM_HT20_TX_PWR_INX_DIFF_2G
				    + offset2 + offset1 * 21] >> (rfpath * 4))
				    & 0xF;
			else
				pwrinfo->ht20indexdiff[rfpath][group] =
				    EEPROM_DEFAULT_HT20_DIFF;
			if (rom_content[EEPROM_OFDM_TX_PWR_INX_DIFF_2G + offset2
			    + offset1 * 21] != 0xFF)
				pwrinfo->ofdmindexdiff[rfpath][group] =
				    (rom_content[EEPROM_OFDM_TX_PWR_INX_DIFF_2G
				     + offset2 + offset1 * 21] >> (rfpath * 4))
				     & 0xF;
			else
				pwrinfo->ofdmindexdiff[rfpath][group] =
				    EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF;
			if (rom_content[EEPROM_HT40_MAX_PWR_OFFSET_2G + offset2
			    + offset1 * 21] != 0xFF)
				pwrinfo->ht40maxoffset[rfpath][group] =
				    (rom_content[EEPROM_HT40_MAX_PWR_OFFSET_2G
				    + offset2 + offset1 * 21] >> (rfpath * 4))
				    & 0xF;
			else
				pwrinfo->ht40maxoffset[rfpath][group] =
				    EEPROM_DEFAULT_HT40_PWRMAXOFFSET;
			if (rom_content[EEPROM_HT20_MAX_PWR_OFFSET_2G + offset2
			    + offset1 * 21] != 0xFF)
				pwrinfo->ht20maxoffset[rfpath][group] =
				    (rom_content[EEPROM_HT20_MAX_PWR_OFFSET_2G +
				     offset2 + offset1 * 21] >> (rfpath * 4)) &
				     0xF;
			else
				pwrinfo->ht20maxoffset[rfpath][group] =
				    EEPROM_DEFAULT_HT20_PWRMAXOFFSET;
		}
	}
	if (rom_content[EEPROM_TSSI_A_5G] != 0xFF) {
		/* 5GL */
		pwrinfo->tssi_a[0] = rom_content[EEPROM_TSSI_A_5G] & 0x3F;
		pwrinfo->tssi_b[0] = rom_content[EEPROM_TSSI_B_5G] & 0x3F;
		/* 5GM */
		pwrinfo->tssi_a[1] = rom_content[EEPROM_TSSI_AB_5G] & 0x3F;
		pwrinfo->tssi_b[1] =
		    (rom_content[EEPROM_TSSI_AB_5G] & 0xC0) >> 6 |
		    (rom_content[EEPROM_TSSI_AB_5G + 1] & 0x0F) << 2;
		/* 5GH */
		pwrinfo->tssi_a[2] = (rom_content[EEPROM_TSSI_AB_5G + 1] &
				      0xF0) >> 4 |
		    (rom_content[EEPROM_TSSI_AB_5G + 2] & 0x03) << 4;
		pwrinfo->tssi_b[2] = (rom_content[EEPROM_TSSI_AB_5G + 2] &
				      0xFC) >> 2;
	} else {
		for (i = 0; i < 3; i++) {
			pwrinfo->tssi_a[i] = EEPROM_DEFAULT_TSSI;
			pwrinfo->tssi_b[i] = EEPROM_DEFAULT_TSSI;
		}
	}
}