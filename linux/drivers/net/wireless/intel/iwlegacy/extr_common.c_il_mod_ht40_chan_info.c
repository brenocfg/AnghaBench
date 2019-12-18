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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct il_priv {int dummy; } ;
struct il_eeprom_channel {int flags; int /*<<< orphan*/  max_power_avg; } ;
struct il_channel_info {int ht40_flags; int /*<<< orphan*/  ht40_extension_channel; int /*<<< orphan*/  ht40_max_power_avg; struct il_eeprom_channel ht40_eeprom; int /*<<< orphan*/  channel; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE ; 
 int /*<<< orphan*/  CHECK_AND_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  D_EEPROM (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int EEPROM_CHANNEL_IBSS ; 
 int EEPROM_CHANNEL_RADAR ; 
 int EEPROM_CHANNEL_VALID ; 
 int /*<<< orphan*/  IBSS ; 
 int /*<<< orphan*/  RADAR ; 
 int /*<<< orphan*/  WIDE ; 
 scalar_t__ il_get_channel_info (struct il_priv*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ il_is_channel_a_band (struct il_channel_info*) ; 
 int /*<<< orphan*/  il_is_channel_valid (struct il_channel_info*) ; 

__attribute__((used)) static int
il_mod_ht40_chan_info(struct il_priv *il, enum nl80211_band band, u16 channel,
		      const struct il_eeprom_channel *eeprom_ch,
		      u8 clear_ht40_extension_channel)
{
	struct il_channel_info *ch_info;

	ch_info =
	    (struct il_channel_info *)il_get_channel_info(il, band, channel);

	if (!il_is_channel_valid(ch_info))
		return -1;

	D_EEPROM("HT40 Ch. %d [%sGHz] %s%s%s%s%s(0x%02x %ddBm):"
		 " Ad-Hoc %ssupported\n", ch_info->channel,
		 il_is_channel_a_band(ch_info) ? "5.2" : "2.4",
		 CHECK_AND_PRINT(IBSS), CHECK_AND_PRINT(ACTIVE),
		 CHECK_AND_PRINT(RADAR), CHECK_AND_PRINT(WIDE),
		 CHECK_AND_PRINT(DFS), eeprom_ch->flags,
		 eeprom_ch->max_power_avg,
		 ((eeprom_ch->flags & EEPROM_CHANNEL_IBSS) &&
		  !(eeprom_ch->flags & EEPROM_CHANNEL_RADAR)) ? "" : "not ");

	ch_info->ht40_eeprom = *eeprom_ch;
	ch_info->ht40_max_power_avg = eeprom_ch->max_power_avg;
	ch_info->ht40_flags = eeprom_ch->flags;
	if (eeprom_ch->flags & EEPROM_CHANNEL_VALID)
		ch_info->ht40_extension_channel &=
		    ~clear_ht40_extension_channel;

	return 0;
}