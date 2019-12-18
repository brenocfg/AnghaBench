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
struct mt76x02_dev {int dummy; } ;
struct mt76_rate_power {void** vht; void** stbc; void** ht; void** ofdm; void** cck; } ;
struct ieee80211_channel {scalar_t__ band; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int MT_EE_TX_POWER_BYRATE_BASE ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  memset (struct mt76_rate_power*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_add_rate_power_offset (struct mt76_rate_power*,int /*<<< orphan*/ ) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76x0_get_delta (struct mt76x02_dev*) ; 
 scalar_t__ mt76x0_tssi_enabled (struct mt76x02_dev*) ; 
 void* s6_to_s8 (int) ; 

void mt76x0_get_tx_power_per_rate(struct mt76x02_dev *dev,
				  struct ieee80211_channel *chan,
				  struct mt76_rate_power *t)
{
	bool is_2ghz = chan->band == NL80211_BAND_2GHZ;
	u16 val, addr;
	s8 delta;

	memset(t, 0, sizeof(*t));

	/* cck 1M, 2M, 5.5M, 11M */
	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_BYRATE_BASE);
	t->cck[0] = t->cck[1] = s6_to_s8(val);
	t->cck[2] = t->cck[3] = s6_to_s8(val >> 8);

	/* ofdm 6M, 9M, 12M, 18M */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 2 : 0x120;
	val = mt76x02_eeprom_get(dev, addr);
	t->ofdm[0] = t->ofdm[1] = s6_to_s8(val);
	t->ofdm[2] = t->ofdm[3] = s6_to_s8(val >> 8);

	/* ofdm 24M, 36M, 48M, 54M */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 4 : 0x122;
	val = mt76x02_eeprom_get(dev, addr);
	t->ofdm[4] = t->ofdm[5] = s6_to_s8(val);
	t->ofdm[6] = t->ofdm[7] = s6_to_s8(val >> 8);

	/* ht-vht mcs 1ss 0, 1, 2, 3 */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 6 : 0x124;
	val = mt76x02_eeprom_get(dev, addr);
	t->ht[0] = t->ht[1] = t->vht[0] = t->vht[1] = s6_to_s8(val);
	t->ht[2] = t->ht[3] = t->vht[2] = t->vht[3] = s6_to_s8(val >> 8);

	/* ht-vht mcs 1ss 4, 5, 6 */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 8 : 0x126;
	val = mt76x02_eeprom_get(dev, addr);
	t->ht[4] = t->ht[5] = t->vht[4] = t->vht[5] = s6_to_s8(val);
	t->ht[6] = t->ht[7] = t->vht[6] = t->vht[7] = s6_to_s8(val >> 8);

	/* ht-vht mcs 1ss 0, 1, 2, 3 stbc */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 14 : 0xec;
	val = mt76x02_eeprom_get(dev, addr);
	t->stbc[0] = t->stbc[1] = s6_to_s8(val);
	t->stbc[2] = t->stbc[3] = s6_to_s8(val >> 8);

	/* ht-vht mcs 1ss 4, 5, 6 stbc */
	addr = is_2ghz ? MT_EE_TX_POWER_BYRATE_BASE + 16 : 0xee;
	val = mt76x02_eeprom_get(dev, addr);
	t->stbc[4] = t->stbc[5] = s6_to_s8(val);
	t->stbc[6] = t->stbc[7] = s6_to_s8(val >> 8);

	/* vht mcs 8, 9 5GHz */
	val = mt76x02_eeprom_get(dev, 0x132);
	t->vht[8] = s6_to_s8(val);
	t->vht[9] = s6_to_s8(val >> 8);

	delta = mt76x0_tssi_enabled(dev) ? 0 : mt76x0_get_delta(dev);
	mt76x02_add_rate_power_offset(t, delta);
}